/*TODO: Add the possiblility to draw objects without setting model matrix*/
/*automatically, heightfield should be derived from object3d*/
/*Continue quadtree_render*/
/*far and near must be calculated correctly in frustum_transform_and_copy*/
#ifdef _WIN32
# include <windows.h>
# include <GL/gl.h>
# include "starglext.h"
#endif

#include <stdlib.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

#include "stargl.h"

#include "heightfield.h"
#include "object3d.h"
#include "matrix.h"
#include "vertex.h"
#include "object_factory.h"
#include "texture.h"
#include "utility.h"
#include "quadtree.h"
#include "camera.h"

/* Texure0 is the detailmap and texture1 is the landmap */
struct heightfield {
  camera cam;
  matrix4 local, world;
  quadtree_node quadtree;
  frustum2d *ftm2d;

  material mat;

  unsigned int w, h;
  double *zvalues;	/* width*height array containing z*sizez values */

  double sizex, sizey, sizez;
  unsigned int patch_sizex;
};


/**********************************************************************/
/* Static function definition                                         */
/**********************************************************************/

static double *create_zvalues(heightfield hf, char *filename);
static object3d create_mesh_stripped_lod(heightfield hf, double sizex, 
					 double sizey, double sizez, int lod);
static object3d create_mesh_patch_stripped_lod(heightfield hf, int px, int py, int lod);
static object3d create_mesh_patch_stripped_lod2(heightfield hf, double px, double py, int lod);

static void quadtree_fill(quadtree_node node, void  *hf);
static void quadtree_set_material(quadtree_node node, void *mat);
static void quadtree_to_opengl(quadtree_node node, void *data);
static void quadtree_set_local_matrix(quadtree_node node, void* local);
static void quadtree_set_world_matrix(quadtree_node node, void* world);
static void quadtree_set_material(quadtree_node node, void* mat);
static void quadtree_render(quadtree_node node, heightfield hf);


/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

heightfield
heightfield_create_from_file(camera cam, char *heightmap_filename,
			     double sizex, double sizey, double sizez)
{
  heightfield hf;
  assert(heightmap_filename);

  hf = (heightfield)malloc(sizeof(struct heightfield));

  hf->sizex = sizex;
  hf->sizey = sizey;
  hf->sizez = sizez;
  hf->patch_sizex = 17;
  hf->cam = cam;

  matrix4_to_scale(hf->local, sizex, sizey, sizez);
  matrix4_copy(hf->world, matrix4_identity);

  hf->zvalues = create_zvalues(hf, heightmap_filename);
  if(!hf->zvalues) {
    free(hf);
    fprintf(stderr, "heightfield_create_from_file: Can't create mesh\n");
    return NULL;
  }

  hf->quadtree = quadtree_create(-0.5f, 0.5, 0.5, -0.5, 5);
  quadtree_foreach_leaf(hf->quadtree, hf, quadtree_fill);

  return hf;  
}

void
heightfield_to_opengl(heightfield hf)
{
  frustum ftm;
  frustum2d ftm2d;
  matrix4 inv;

  matrix4_mul(inv, hf->local, hf->world);
  matrix4_to_inverse(inv);
  frustum_transform_and_copy(&ftm, &hf->cam->ftm, inv, &hf->cam->pos);
  ftm.near.d = -0.05;
  ftm.far.d = 1000;

  frustum_to_frustum2d(&ftm2d, &ftm);
  hf->ftm2d = &ftm2d;


  printf("TRANS:\n");
  frustum_print(&ftm);
  printf("\n");

  quadtree_render(hf->quadtree, hf);
  //  quadtree_foreach_leaf(hf->quadtree, hf, quadtree_to_opengl);
}

/************************************************************************/
/* Getters and Setters                                                  */
/************************************************************************/
void
heightfield_set_textures_from_file(heightfield hf, char *land, char *details)
{
  texture tex[2];
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

  hf->mat = material_create(tex, 2, NULL, 0, 0);
  quadtree_foreach_leaf(hf->quadtree, hf->mat, quadtree_set_material);
}

void
heightfield_set_detail_scale(heightfield hf, double sx, double sy)
{
  matrix4 scale;
  texture tex = material_get_texture(hf->mat, 0);

  matrix4_to_scale(scale, sx, sy, 1);
  texture_set_matrix(tex, scale);
}

void
heightfield_set_local_matrix(heightfield hf, matrix4 local)
{
  matrix4_copy(hf->local, local);
  quadtree_foreach_leaf(hf->quadtree, local, quadtree_set_local_matrix);
}

void
heightfield_set_world_matrix(heightfield hf, matrix4 world)
{
  matrix4_copy(hf->world, world);
  quadtree_foreach_leaf(hf->quadtree, world, quadtree_set_world_matrix);
}

matrix4 *
heightfield_get_world_matrix(heightfield hf)
{
  return &hf->world;
}

matrix4 *
heightfield_get_local_matrix(heightfield hf)
{
  return &hf->local;
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

/*This function creates the patch (px,py) with lod lod*/
static object3d
create_mesh_patch_stripped_lod(heightfield hf, int px, int py, int lod)
{
  matrix4 local;
  vertexbuffer vb;
  unsigned int w, h, step;
  unsigned int num_vert;

  px *= hf->patch_sizex-1;
  py *= hf->patch_sizex-1;

  w = hf->w;
  h = hf->h;
  step = (1<<lod);

  num_vert = (unsigned int)((2*ceil((double)hf->patch_sizex/step)+2)*(ceil((double)hf->patch_sizex/step)-1));
  vb = vertexbuffer_create(VB_SYSTEM, TRIANGLES_STRIP, num_vert, 0);

  vertexbuffer_lock(vb);
  {
    vertex *vertices = vertexbuffer_get_vertices(vb);
    double *z = hf->zvalues;
    unsigned int i, j, k = 0, ofs = px+py*w;
    unsigned int next_line = step*w;
    double stepu = (double)step/w;
    double stepv = -(double)step/h;
    double stepx = (double)step/w;
    double stepy = (double)step/h;
    double u, v = -py*stepv, x, y = 0.5-py*stepy;

    for(j = 0; j < hf->patch_sizex-1; j+=step) {
      unsigned int old_k = k+1;	/* Second vertex of the row */
      for(i = 0, u = px*stepu, x = -0.5+px*stepx; i < hf->patch_sizex; i+=step, ofs+=step) {
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
      ofs += next_line-hf->patch_sizex-(step-1);
      vertex_copy(&vertices[k], &vertices[k-1]);
      vertex_copy(&vertices[k+1], &vertices[old_k]);
      k+=2;
      v -= stepv;
      y -= stepy;
    }
  }
  vertexbuffer_unlock(vb);

  matrix4_to_scale(local, hf->sizex, hf->sizey, hf->sizez);

  return object3d_create(local, matrix4_identity, vb, NULL);
}

/*Transform (px,py) in patch unit coordinate and draw the corresponding patch*/
static object3d
create_mesh_patch_stripped_lod2(heightfield hf, double px, double py, int lod)
{
  int cellx = (int)((px+0.5)*256.0f/16);
  int celly = (int)((-py+0.5)*256.0f/16);

  //    printf("%d %d %f %f\n", cellx, celly, px, py);
  
  return create_mesh_patch_stripped_lod(hf, cellx, celly, lod);
}

static void
quadtree_fill(quadtree_node node, void  *hf)
{
  node->data = create_mesh_patch_stripped_lod2((heightfield)hf, node->box.corners[0].x, node->box.corners[0].y, 0);
}

static void
quadtree_set_material(quadtree_node node, void *mat)
{
  object3d_set_material((object3d)node->data, (material)mat);
}

static void
quadtree_set_world_matrix(quadtree_node node, void *world)
{
  object3d_set_world_matrix((object3d)node->data, (double **)world);
}

static void
quadtree_set_local_matrix(quadtree_node node, void *local)
{
  object3d_set_world_matrix((object3d)node->data, (double **)local);
}

static void
quadtree_to_opengl(quadtree_node node, void *data)
{
  object3d_to_opengl((object3d)node->data);
}

static void
quadtree_render(quadtree_node node, heightfield hf)
{
  if(node->childs[0] == NULL || node->childs[1] == NULL ||
     node->childs[2] == NULL || node->childs[3] == NULL) {
    object3d_to_opengl((object3d)node->data);
    return;
  }

  if(frustum2d_bbox_is_into(hf->ftm2d, &node->childs[0]->box))
     quadtree_render(node->childs[0], hf);
  if(frustum2d_bbox_is_into(hf->ftm2d, &node->childs[1]->box)) 
     quadtree_render(node->childs[1], hf);
  if(frustum2d_bbox_is_into(hf->ftm2d, &node->childs[2]->box))
     quadtree_render(node->childs[2], hf);
  if(frustum2d_bbox_is_into(hf->ftm2d, &node->childs[3]->box))
     quadtree_render(node->childs[3], hf);
}

/***********************************************************************/
/* Trash                                                               */
/***********************************************************************/

#if 0
static object3d
create_mesh_indexed(heightfield hf, double sizex, double sizey, double sizez)
{
  matrix4 local;
  object3d obj;
  unsigned int pitch;
  int w,h;
  vertexbuffer vb;

  w = hf->w;
  h = hf->h;

  /*  obj = create_plan_xz(sizex, sizey, w-1, h-1);*/
  obj = create_plan_xy(1, 1, w-1, h-1);
  vb = object3d_get_vertexbuffer(obj);

  vertexbuffer_lock(vb);
  {
    vertex *vertices = vertexbuffer_get_vertices(vb);
    unsigned int i, j, ofs = 0;
    double u=0,v=0;
    double stepu = 1.0/(w-1);
    double stepv = 1.0/(h-1);

    for(j=0; j < h; j++) {
      for(i=0; i < w; i++) {
	vertices[ofs].coord.z = hf->zvalues[ofs];
	vertex_set_tcoord(&vertices[ofs], 0, u, v);
	vertex_set_tcoord(&vertices[ofs], 1, u, v);
	u+=stepu;
	ofs++;
      }
      u=0;
      v+=stepv;
    }
  }
  vertexbuffer_unlock(vb);

  matrix4_to_scale(local, sizex, sizey, sizez);
  object3d_set_local_matrix(obj, local);

  return obj;
}
#endif
