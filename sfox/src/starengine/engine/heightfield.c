#include <stdlib.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

#include "heightfield.h"
#include "object3d.h"
#include "matrix.h"
#include "vertex.h"
#include "object_factory.h"
#include "texture.h"
#include "utility.h"

/* Texure0 is the detailmap and texture1 is the landmap */
struct heightfield {
  object3d obj;
  unsigned int w, h;
  double *zvalues;	/* width*height array containing z*sizez values */
};


/**********************************************************************/
/* Static function definition                                         */
/**********************************************************************/

static double *create_zvalues(heightfield hf, char *filename);
static object3d create_mesh_stripped(heightfield hf, double sizex, 
				     double sizey);
static object3d create_mesh_stripped_lod(heightfield hf, double sizex, 
					 double sizey, double sizez, int lod);

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

heightfield
heightfield_create_from_file(char *heightmap_filename, double sizex,
			     double sizey, double sizez)
{
  object3d obj;
  heightfield hf;
  assert(heightmap_filename);


  hf = (heightfield)malloc(sizeof(struct heightfield));
  hf->zvalues = create_zvalues(hf, heightmap_filename);
  if(!hf->zvalues) {
    free(hf);
    fprintf(stderr, "heightfield_create_from_file: Can't create mesh\n");
    return NULL;
  }

  hf->obj = create_mesh_stripped_lod(hf, sizex, sizey, sizez, 0);
  if(!hf->obj) {
    free(hf->zvalues);
    free(hf);
    fprintf(stderr, "heightfield_create_from_file: Can't create mesh\n");
    return NULL;
  }

  return hf;  
}

void
heightfield_to_opengl(heightfield hf)
{
  object3d_to_opengl(hf->obj);
}

/************************************************************************/
/* Getters and Setters                                                  */
/************************************************************************/
void
heightfield_set_textures_from_file(heightfield hf, char *land, char *details)
{
  texture tex[2];
  material mat;
  assert(land&&details);

  tex[0] = texture_create_from_file(details);
  tex[1] = texture_create_from_file(land);

  texture_add_texture_env(tex[0], GL_TEXTURE_ENV_MODE, GL_REPLACE);
  texture_add_texture_env(tex[1], GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
  texture_add_texture_env(tex[1], GL_RGB_SCALE_ARB, 2);

  texture_set_min_filter_mode(tex[0], LINEAR_MIPMAP_LINEAR);
  texture_set_mag_filter_mode(tex[0], LINEAR);
  texture_set_min_filter_mode(tex[1], LINEAR_MIPMAP);
  texture_set_mag_filter_mode(tex[1], LINEAR);

  mat = material_create(tex, 2, NULL, 0, 0);
  object3d_set_material(hf->obj, mat);
}

void
heightfield_set_detail_scale(heightfield hf, double sx, double sy)
{
  texture tex = material_get_texture(object3d_get_material(hf->obj), 0);
  matrix4 scale;

  matrix4_to_scale(scale, sx, sy, 1);
  texture_set_matrix(tex, scale);
}

object3d
heightfield_get_object(heightfield hf)
{
  return hf->obj;
}

void
heightfield_set_local_matrix(heightfield hf, matrix4 local)
{
  object3d_set_local_matrix(hf->obj, local);
}

void
heightfield_set_world_matrix(heightfield hf, matrix4 world)
{
  object3d_set_world_matrix(hf->obj, world);
}

matrix4 *
heightfield_get_world_matrix(heightfield hf)
{
  return object3d_get_world_matrix(hf->obj);
}

matrix4 *
heightfield_get_local_matrix(heightfield hf)
{
  return object3d_get_local_matrix(hf->obj);
}

/****************************************************************************/
/* Local functions                                                          */
/****************************************************************************/

/* Convert 8bit heightmap in double heightmap*/
static double *
create_zvalues(heightfield hf, char *filename)
{
  double *zvalues;
  unsigned int i, j, k;
  unsigned char *pixels;
  SDL_Surface *image = IMG_Load(filename);

  if(!image) {
    fprintf(stderr, "create_zvalues: Can't load heights file %s\n", filename);
    return NULL;
  }

  SDL_LockSurface(image);
 
  zvalues = malloc(sizeof(double)*image->w*image->h);
  hf->w = image->w;
  hf->h = image->h;
  pixels = image->pixels;

  for(k = 0, j = 0; j < image->h; j++)
    for(i = 0; i < image->w; i++)
      zvalues[k++] = (double)pixels[i+j*image->pitch]/255;
  
  SDL_UnlockSurface(image);
  SDL_FreeSurface(image);

  return zvalues;
}

/*This function creates a heightfield of size(1,1,1) and fill the local*/
/*matrix with a scale matrix*/
/*lod starts at 0*/
static object3d
create_mesh_stripped_lod(heightfield hf, double sizex, double sizey, double sizez, int lod)
{
  matrix4 local;
  object3d obj;
  vertexbuffer vb;
  unsigned int w, h, step;
  unsigned int num_vert;

  w = hf->w;
  h = hf->h;
  step = (1<<lod);

  num_vert = (unsigned int)((2*ceil((double)w/step)+2)*(ceil((double)h/step)-1));
  vb = vertexbuffer_create(VB_STATIC_DRAW, TRIANGLES_STRIP, num_vert, 0);

  vertexbuffer_lock(vb);
  {
    vertex *vertices = vertexbuffer_get_vertices(vb);
    double *z = hf->zvalues;
    unsigned int i, j, k = 0, ofs = 0;
    unsigned int next_line = step*w;
    double u=0, v=0, x, y = 0.5;
    double stepu = (double)step/w;
    double stepv = -(double)step/h;
    double stepx = (double)step/w;
    double stepy = (double)step/h;

    for(j = 0; j < h-1; j+=step) {
      unsigned int old_k = k+1;	/* Second vertex of the row */
      for(i = 0, u = 0, x = -0.5; i < w; i+=step, ofs+=step) {
	vertex_set_coord(&vertices[k], x, y, z[ofs]);
	vertex_set_coord(&vertices[k+1], x, y-stepy, z[ofs+next_line]);
	vertex_set_tcoord(&vertices[k], 0, u, v);
	vertex_set_tcoord(&vertices[k], 1, u, v);
	vertex_set_tcoord(&vertices[k+1], 0, u, v-stepv);
	vertex_set_tcoord(&vertices[k+1], 1, u, v-stepv);
	k+=2;
	x += stepx;
	u += stepu;
      }
      ofs += next_line-w-(step-1);
      vertex_copy(&vertices[k], &vertices[k-1]);
      vertex_copy(&vertices[k+1], &vertices[old_k]);
      k+=2;
      v -= stepv;
      y -= stepy;
    }
  }
  vertexbuffer_unlock(vb);

  matrix4_to_scale(local, sizex, sizey, sizez);

  return object3d_create(local, matrix4_identity, vb, NULL);
}
