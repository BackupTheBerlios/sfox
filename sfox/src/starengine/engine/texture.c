#ifdef _WIN32
# include <windows.h>
# include <GL/gl.h>
# include "starglext.h"
#endif /*_WIN32*/

#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#include "starengine.h"
#include "starutils.h"
#include "stargl.h"
#include "starglu.h"

#include "texture.h"
#include "dds.h"
#include "matrix.h"
#include "utility.h"

static const GLuint clamp_mode[] = { GL_CLAMP, GL_CLAMP_TO_EDGE, GL_REPEAT };
static const GLuint filter_mode[] = { GL_NEAREST, GL_LINEAR, 
				      GL_NEAREST_MIPMAP_NEAREST,
				      GL_LINEAR_MIPMAP_NEAREST,
				      GL_NEAREST_MIPMAP_LINEAR,
				      GL_LINEAR_MIPMAP_LINEAR };
static const GLuint data_kind[] = { GL_UNSIGNED_BYTE, GL_UNSIGNED_INT};
static const GLuint pixel_format[] = { GL_RGB, GL_RGBA, GL_ALPHA };

struct texture {
  GLuint tex_name;
  SSList *texture_env;
  matrix4 m;
};


static texture texture_create_from_standard_file(char *filename);
static texture texture_create_from_dds(char *filename);
static texture texture_create_empty();

static void texture_env_to_opengl(texture tex);

texture
texture_create_from_file(char *filename)
{
  int len = strlen(filename);
  
  if(len > strlen(".DDS"))
    if(strcasecmp(filename+len-strlen(".DDS"), ".DDS") == 0)
      return texture_create_from_dds(filename);

  return texture_create_from_standard_file(filename);
}

void
texture_set_st_clamp_mode(texture tex, clampmode mode)
{
  glBindTexture(GL_TEXTURE_2D, tex->tex_name);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp_mode[mode]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp_mode[mode]);
}

void
texture_set_min_filter_mode(texture tex, filtermode mode)
{
  glBindTexture(GL_TEXTURE_2D, tex->tex_name);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_mode[mode]);
}

void
texture_set_mag_filter_mode(texture tex, filtermode mode)
{
  assert(mode==LINEAR||mode==NEAREST);
  glBindTexture(GL_TEXTURE_2D, tex->tex_name);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_mode[mode]);
}

void
texture_bind(texture tex)
{
  glBindTexture(GL_TEXTURE_2D, tex->tex_name);
}

void
texture_destroy(texture tex)
{
  glDeleteTextures(1, &tex->tex_name);
  s_slist_free(tex->texture_env);
  tex->texture_env = NULL;

  free(tex);
}

void
texture_set_matrix(texture tex, matrix4 m)
{
  matrix4_copy(tex->m, m);
}

void
texture_add_texture_env(texture tex, unsigned int pname, unsigned int param)
{
  tex->texture_env = s_slist_append(tex->texture_env, SUINT_TO_POINTER(pname));
  tex->texture_env = s_slist_append(tex->texture_env, SUINT_TO_POINTER(param));
}

void
texture_copy_from_image(texture tex, void *pixels, int offsetx, int offsety,
			unsigned int width, unsigned int height, 
			pixelfmt pix_format, datatype data_type)
{
  texture_bind(tex);
  glTexSubImage2D(GL_TEXTURE_2D, 0, offsetx, offsety, width, height, 
		  pixel_format[pix_format], data_kind[data_type], pixels);
}

void
texture_to_opengl(texture tex)
{
  glBindTexture(GL_TEXTURE_2D, tex->tex_name);
  texture_env_to_opengl(tex);

  glMatrixMode(GL_TEXTURE);
  glLoadMatrixd((double *)tex->m);
  glMatrixMode(GL_MODELVIEW);
}

/****************************************************************************/
/* Local function */
/****************************************************************************/

/* Execute the glTexEnvi list */
static void
texture_env_to_opengl(texture tex)
{
  SSList *elem = tex->texture_env;
  unsigned int pname, param;

  while(elem) {
    pname = (unsigned int)elem->data;
    elem = elem->next;
    assert(elem);
    param = (unsigned int)elem->data;
    glTexEnvi(GL_TEXTURE_ENV, pname, param);  
    elem = s_slist_next(elem);
  }    

}

/* Load from a tga, jpg... Any format supported by SDL_Image */
static texture
texture_create_from_standard_file(char *filename)
{
  texture tex = NULL;
  SDL_Surface *image = IMG_Load(filename);

  if(image) {
    int type;

    tex = texture_create_empty();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, tex->tex_name);

    if(image->format->BytesPerPixel == 4)
      type = GL_RGBA;
    else
      type = GL_RGB;

    SDL_LockSurface(image);
    gluBuild2DMipmaps(GL_TEXTURE_2D, type, image->w, image->h,
		      type, GL_UNSIGNED_BYTE, image->pixels);
    SDL_UnlockSurface(image);
    SDL_FreeSurface(image);
  }
  
  if(!tex)
    fprintf(stderr, "texture_create_from_standard_file: Can't create texture %s\n", filename);

  return tex;
}

/* Load texture from a DDS texture file */
static texture
texture_create_from_dds(char *filename)
{
  texture tex = NULL;
  ddstexture dds = dds_load_from_file(filename);

  if(dds) {
    unsigned int i;

    tex = texture_create_empty();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, tex->tex_name);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, dds->mipmap_count-1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    for(i = 0; i < dds->mipmap_count; i++)
      glCompressedTexImage2D(GL_TEXTURE_2D, i, dds->dxt_version,
			     dds->mipmaps[i]->width,
			     dds->mipmaps[i]->height,
			     0, dds->mipmaps[i]->size, 
			     dds->mipmaps[i]->pixels);
    dds_destroy(dds);
  }

  if(!tex)
    fprintf(stderr, "texture_create_from_dds: Can't create texture %s\n", filename);

  return tex;
}

static texture
texture_create_empty()
{
  texture tex = malloc(sizeof(struct texture));

  tex->texture_env = NULL;
  glGenTextures(1, &tex->tex_name);
  matrix4_to_identity(tex->m);

  return tex;
}
