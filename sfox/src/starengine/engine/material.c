#ifdef _WIN32
# include <windows.h>
# include <GL/gl.h>
# include "starglext.h"
#endif /*_WIN32*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "starengine.h"
#include "stargl.h"

#include "material.h"
#include "engineconst.h"
#include "texture.h"
#include "color.h"

struct material {
  texture tex[MAX_TEXTURES];	/* Ends with NULL(?) */
  unsigned int num_textures;
  unsigned int active_flag;
  color col;
  double diffuse;
  double specular;
};

material
material_create(texture tex[], int num_textures, color *col, double diffuse, double specular)
{
  material mat = malloc(sizeof(struct material));
  assert(mat);

  
  memset(mat->tex, 0, MAX_TEXTURES*sizeof(texture));
  mat->active_flag = 0;

  if(col) {
    mat->active_flag |= COLOR;
    color_copy(&mat->col, col);
  }

  if(diffuse != 0) {
    mat->active_flag |= DIFFUSE;
    mat->diffuse = diffuse;
  }

  if(specular != 0) {
    mat->active_flag |= SPECULAR;
    mat->specular = specular;
  }

  if(num_textures != 0) {
    assert(num_textures<=MAX_TEXTURES);
    memcpy(mat->tex, tex, sizeof(texture)*num_textures);
    mat->num_textures = num_textures;
    mat->active_flag |= TEXTURE;
  }

  return mat;
}

material
material_create_single_texture_from_file(char *filename)
{
  texture tex = texture_create_from_file(filename);

  if(tex == NULL)
    return NULL;
  texture_add_texture_env(tex, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  return material_create(&tex, 1, NULL, 0, 0);
}

void
material_to_opengl(material mat)
{
  unsigned int i;

  if(mat->active_flag&COLOR) {
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_COLOR_ARRAY);
    glColor4d(mat->col.r, mat->col.g, mat->col.b, mat->col.a);
  }

  i = 0;
  if(mat->active_flag&TEXTURE)
    for(i = 0; i < mat->num_textures; i++) {
      glActiveTexture(GL_TEXTURE0+i);
      glEnable(GL_TEXTURE_2D); /* Activate usued textures stage */      
      texture_to_opengl(mat->tex[i]);
      glClientActiveTexture(GL_TEXTURE0+i);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
  for(; i < MAX_TEXTURES; i++) {
    glActiveTexture(GL_TEXTURE0+i);
    glDisable(GL_TEXTURE_2D);	/* Desactivate unusued textures unit */
    glClientActiveTexture(GL_TEXTURE0+i);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
}

void
material_destroy(material mat)
{
  free(mat);
}

texture
material_get_texture(material mat, int num)
{
  assert(num<mat->num_textures);
  return mat->tex[num];
}
