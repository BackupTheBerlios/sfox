#ifdef _WIN32
# include <windows.h>
# include "stargl.h"
# include "starglext.h"
# include "starglaux.h"
#endif /*_WIN32*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stargl.h"
#include "dds.h"

#define MAGICID "DDS "

#ifndef MAX
#define MAX(x,y) (((x)>(y))?(x):(y))
#endif

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)\
                ((unsigned int)(unsigned char)(ch0) | \
                ((unsigned int)(unsigned char)(ch1) << 8) |  \
                ((unsigned int)(unsigned char)(ch2) << 16) | \
                ((unsigned int)(unsigned char)(ch3) << 24 ))
#endif //MAKEFOURCC

#define FOURCC_DXT1 MAKEFOURCC('D', 'X', 'T', '1')
#define FOURCC_DXT2 MAKEFOURCC('D', 'X', 'T', '2')
#define FOURCC_DXT3 MAKEFOURCC('D', 'X', 'T', '3')
#define FOURCC_DXT4 MAKEFOURCC('D', 'X', 'T', '4')
#define FOURCC_DXT5 MAKEFOURCC('D', 'X', 'T', '5')

/* DDSURFACEDESC.dwFlags */
#define DDSD_CAPS               0x00000001
#define DDSD_HEIGHT             0x00000002
#define DDSD_WIDTH              0x00000004
#define DDSD_PITCH              0x00000008
#define DDSD_BACKBUFFERCOUNT    0x00000020
#define DDSD_ZBUFFERBITDEPTH    0x00000040
#define DDSD_ALPHABITDEPTH      0x00000080
#define DDSD_LPSURFACE          0x00000800
#define DDSD_PIXELFORMAT        0x00001000
#define DDSD_CKDESTOVERLAY      0x00002000
#define DDSD_CKDESTBLT          0x00004000
#define DDSD_CKSRCOVERLAY       0x00008000
#define DDSD_CKSRCBLT           0x00010000
#define DDSD_MIPMAPCOUNT        0x00020000
#define DDSD_REFRESHRATE        0x00040000
#define DDSD_LINEARSIZE         0x00080000
#define DDSD_TEXTURESTAGE       0x00100000
#define DDSD_FVF                0x00200000
#define DDSD_SRCVBHANDLE        0x00400000
#define DDSD_ALL                0x007ff9ee

/* DDCOLORKEY.dwFlags */
#define DDPF_ALPHAPIXELS                0x00000001
#define DDPF_ALPHA                      0x00000002
#define DDPF_FOURCC                     0x00000004
#define DDPF_PALETTEINDEXED4            0x00000008
#define DDPF_PALETTEINDEXEDTO8          0x00000010
#define DDPF_PALETTEINDEXED8            0x00000020
#define DDPF_RGB                        0x00000040
#define DDPF_COMPRESSED                 0x00000080
#define DDPF_RGBTOYUV                   0x00000100
#define DDPF_YUV                        0x00000200
#define DDPF_ZBUFFER                    0x00000400
#define DDPF_PALETTEINDEXED1            0x00000800
#define DDPF_PALETTEINDEXED2            0x00001000
#define DDPF_ZPIXELS                    0x00002000
#define DDPF_STENCILBUFFER              0x00004000
#define DDPF_ALPHAPREMULT               0x00008000
#define DDPF_LUMINANCE                  0x00020000
#define DDPF_BUMPLUMINANCE              0x00040000
#define DDPF_BUMPDUDV                   0x00080000

#define DDS_REQUIRED_FLAGS (DDSD_CAPS|DDSD_PIXELFORMAT|DDSD_WIDTH|DDSD_HEIGHT)

struct DDPIXELFORMAT {
  unsigned int dwSize;
  unsigned int dwFlags;
  unsigned int dwFourCC;
  unsigned int dwRGBBitCount;
  unsigned int dwRBitMask;
  unsigned int dwGBitMask;
  unsigned int dwBBitMask;
  unsigned int dwRGBAlphaBitMask;
};

struct DDCAPS2 {
  unsigned int dwCaps1;
  unsigned int dwCaps2;
  unsigned int Reserved[2];
};

struct DDSURFACEDESC2 {
  unsigned int dwSize;
  unsigned int dwFlags;
  unsigned int dwHeight;
  unsigned int dwWidth;
  unsigned int dwPitchOrLinearSize;
  unsigned int dwDepth;
  unsigned int dwMipMapCount;
  unsigned int dwReserved1[11];
  struct DDPIXELFORMAT ddpfPixelFormat;
  struct DDCAPS2  ddsCaps;
  unsigned int dwReserved2;
};

#ifndef _WIN32
typedef unsigned int FOURCC;
#endif

static unsigned int calc_mipmap_size(unsigned int width, unsigned int height, int dxt_version);

ddstexture
dds_load_from_file(char *filename)
{
  unsigned int i,mipmap_size, offset = 0;
  unsigned int width, height;
  struct DDSURFACEDESC2 ddsd;
  ddstexture dds_ret;
  unsigned char *data;
  long size;
  FILE *file = fopen(filename, "rb");

  if(!file) {
    fprintf(stderr, "dds_load: Can't open file %s\n", filename);
    return NULL;
  }

  dds_ret = calloc(1, sizeof(struct ddstexture));

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  data = malloc(size);
  if(fread(data, sizeof(char), size, file) != size) {
    fprintf(stderr, "dds_load: Can't read file\n");
    goto error;
  }

  if(strncmp(data, MAGICID, strlen(MAGICID)!=0)) {
    fprintf(stderr, "dds_load: Not a DDS file\n");
    goto error;
  }
  
  offset += strlen(MAGICID);
  memcpy(&ddsd, data+offset, sizeof(struct DDSURFACEDESC2));

  if((ddsd.dwFlags&DDS_REQUIRED_FLAGS) != DDS_REQUIRED_FLAGS ||
     ddsd.dwSize != 124)
    {
      fprintf(stderr, "dds_load: Bad DDS file\n");
      goto error;
    }

  dds_ret->width = ddsd.dwWidth;
  dds_ret->height = ddsd.dwHeight;

  if(ddsd.dwFlags&DDSD_LINEARSIZE)
    dds_ret->linearsize = ddsd.dwPitchOrLinearSize;

  if(ddsd.dwFlags&DDSD_MIPMAPCOUNT)
    dds_ret->mipmap_count = ddsd.dwMipMapCount;

  if(ddsd.ddpfPixelFormat.dwSize != 32) {
    fprintf(stderr, "dds_load: Bad DDS file\n");
    goto error;
  }

  if(!ddsd.ddpfPixelFormat.dwFlags&DDPF_FOURCC) {
    fprintf(stderr, "dds_load: Uncompressed DDS not supported\n");
    goto error;
  }

  switch(ddsd.ddpfPixelFormat.dwFourCC) {
      case FOURCC_DXT1:
	dds_ret->dxt_version = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	break;
      case FOURCC_DXT3:
	dds_ret->dxt_version = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	break;
      case FOURCC_DXT5:
	dds_ret->dxt_version = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	break;
      default:
	fprintf(stderr, "dds_load: Unknown DXT version\n");
	goto error;
	break;
  }    

  dds_ret->mipmaps = malloc(sizeof(struct dds_mipmaps *)*dds_ret->mipmap_count);
  offset += sizeof(struct DDSURFACEDESC2);
  mipmap_size = dds_ret->linearsize;
  width = dds_ret->width;
  height = dds_ret->height;

  for(i = 0; i < dds_ret->mipmap_count; i++) {
    dds_ret->mipmaps[i] = malloc(sizeof(struct dds_mipmaps));
    dds_ret->mipmaps[i]->width = MAX(width, 1);
    dds_ret->mipmaps[i]->height = MAX(height, 1);
    dds_ret->mipmaps[i]->size = calc_mipmap_size(width, height, dds_ret->dxt_version);
    dds_ret->mipmaps[i]->pixels = malloc(dds_ret->mipmaps[i]->size);
    memcpy(dds_ret->mipmaps[i]->pixels, data+offset, dds_ret->mipmaps[i]->size);
    offset += dds_ret->mipmaps[i]->size;
    width >>= 1;
    height >>= 1;
  }

  free(data);
  fclose(file);

  return dds_ret;

error:
  free(dds_ret);
  free(data);
  fclose(file);

  return NULL;
}

void
dds_destroy(ddstexture dds_tex)
{
  unsigned int i;
  assert(dds_tex);

  for(i = 0; i < dds_tex->mipmap_count; i++) {
    free(dds_tex->mipmaps[i]->pixels);
    dds_tex->mipmaps[i]->pixels = NULL;
    free(dds_tex->mipmaps[i]);
  }
  free(dds_tex->mipmaps);
  dds_tex->mipmaps = NULL;
  free(dds_tex);
}

static unsigned int
calc_mipmap_size(unsigned int width, unsigned int height, int dxt_version)
{
  if(dxt_version == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
     dxt_version == GL_COMPRESSED_RGB_S3TC_DXT1_EXT)
    return MAX(1, width/4)*MAX(1, height/4)*8;
  else
    return MAX(1, width/4)*MAX(1, height/4)*16;
}
