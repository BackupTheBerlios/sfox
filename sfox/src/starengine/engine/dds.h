#ifndef DDS_H
#define DDS_H

struct dds_mipmaps {
  unsigned char *pixels;
  unsigned int size;
  unsigned int width;
  unsigned int height;
};

typedef struct ddstexture {
  unsigned int width, height, linearsize;
  unsigned int mipmap_count;
  struct dds_mipmaps **mipmaps;
  unsigned int dxt_version;     /* GL_COMPRESSED_RGBA_S3TC_DXT[1-5]_EXT */
} *ddstexture;

extern ddstexture dds_load_from_file(char *filename);
extern void dds_destroy(ddstexture dds_tex);


#endif
