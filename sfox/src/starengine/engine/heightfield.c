/*TODO: Add the possiblility to draw objects without setting model matrix*/
/*automatically, heightfield should be derived from object3d*/
/*Continue quadtree_render*/
/*far and near must be calculated correctly in frustum_transform_and_copy*/
/*BUG: when the camera is at y=0 everything is ok*/
/*y!=0 culling culls too much*/
/*create_mesh_patch_stripped_lod(heightfield hf, int px, int py, int lod)*/
/*TODO: pass directly x,y to create_mesh_patch_stripped_lod */
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
  object3d obj;

  camera cam;
  quadtree_node quadtree;
  frustum2d *ftm2d;

  unsigned int w, h;
  float *zvalues;	/* width*height array containing z*sizez values */

  float sizex, sizey, sizez;
  unsigned int patch_sizex;
};


/**********************************************************************/
/* Static function definition                                         */
/**********************************************************************/

static float *create_zvalues(heightfield hf, char *filename);
static object3d *create_mesh_patch_stripped_lod2(heightfield hf, float x, float y, int lod);
static object3d *create_mesh_patch_stripped_lod_list(heightfield hf, float x, float y, int px, int py, int lod);

static void quadtree_fill(quadtree_node node, void  *hf);
static void quadtree_set_material(quadtree_node node, void *mat);
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

  object3d_init(&hf->obj, matrix4_identity, NULL, NULL);
  hf->sizex = sizex;
  hf->sizey = sizey;
  hf->sizez = sizez;
  hf->patch_sizex = 17;
  hf->cam = cam;

  object3d_set_world_matrix(SF_OBJECT3D(hf), matrix4_identity);

  hf->zvalues = create_zvalues(hf, heightmap_filename);
  if(!hf->zvalues) {
    free(hf);
    fprintf(stderr, "heightfield_create_from_file: Can't create mesh\n");
    return NULL;
  }

  hf->quadtree = quadtree_create(-hf->sizex/2, -hf->sizey/2, hf->sizex/2, hf->sizey/2, 4);
  quadtree_foreach_leaf(hf->quadtree, hf, quadtree_fill);

  return hf;  
}

void
heightfield_to_opengl(heightfield hf)
{
  frustum2d ftm2d;

  frustum_to_frustum2d_xz(&ftm2d, &hf->cam->ftm);
  hf->ftm2d = &ftm2d;

  //printf("TRANS:\n");
  //frustum_print(&hf->cam->ftm);
  //printf("\n");

  quadtree_render(hf->quadtree, hf);
}

static void
quadtree_render(quadtree_node node, heightfield hf)
{
  if(node->childs[0] == NULL || node->childs[1] == NULL ||
     node->childs[2] == NULL || node->childs[3] == NULL) {
    object3d_to_opengl((object3d *)node->data);
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

  SF_OBJECT3D(hf)->mat = material_create(tex, 2, NULL, 0, 0);
  quadtree_foreach_leaf(hf->quadtree, SF_OBJECT3D(hf)->mat, quadtree_set_material);
}

void
heightfield_set_detail_scale(heightfield hf, double sx, double sy)
{
  matrix4 scale;
  texture tex = material_get_texture(SF_OBJECT3D(hf)->mat, 0);

  matrix4_to_scale(scale, sx, sy, 1);
  texture_set_matrix(tex, scale);
}

void
heightfield_set_world_matrix(heightfield hf, matrix4 world)
{
  matrix4_copy(SF_OBJECT3D(hf)->world, world);
}

matrix4 *
heightfield_get_world_matrix(heightfield hf)
{
  return &SF_OBJECT3D(hf)->world;
}

/****************************************************************************/
/* Local functions                                                          */
/****************************************************************************/

/* Convert 8bit heightmap in double heightmap*/
static float *
create_zvalues(heightfield hf, char *filename)
{
  float *zvalues;
  unsigned int i, j, k;
  unsigned char *pixels;
  SDL_Surface *image = IMG_Load(filename);

  if(!image) {
    fprintf(stderr, "create_zvalues: Can't load heights file %s\n", filename);
    return NULL;
  }

  SDL_LockSurface(image);
 
  zvalues = malloc(sizeof(float)*image->w*image->h);
  hf->w = image->w;
  hf->h = image->h;
  pixels = image->pixels;

  for(k = 0, j = 0; j < image->h; j++)
    for(i = 0; i < image->w; i++)
      zvalues[k++] = (hf->sizez*(float)pixels[i+j*image->pitch])/255;
  
  SDL_UnlockSurface(image);
  SDL_FreeSurface(image);

  return zvalues;
}

/*Use display lists for patches*/
static object3d *
create_mesh_patch_stripped_lod_list(heightfield hf, float x, float y, int px, int py, int lod)
{
  object3d *obj = object3d_create(matrix4_identity, NULL, NULL);
  unsigned int w, h, step;

  px *= hf->patch_sizex-1;
  py *= hf->patch_sizex-1;

  w = hf->w;
  h = hf->h;
  step = (1<<lod);
  
  {
    float *z = hf->zvalues;
    unsigned int i, j, ofs = px+py*w;
    unsigned int next_line = step*w;
    float stepu = (float)step/w;
    float stepv = -(float)step/h;
    float stepx = step*hf->sizex/w;
    float stepy = step*hf->sizey/h;
    float u, v = -py*stepv;

    //printf("x=%f y=%f newx=%f newy=%f\n", x, y, -hf->sizex/2+px*stepx, -hf->sizey/2+py*stepy);
    y = -hf->sizey/2+py*stepy;

    object3d_BeginList(obj);
    object3d_Begin(GL_TRIANGLE_STRIP);
    for(j = 0; j < hf->patch_sizex-1; j+=step) {
      for(i = 0, u = px*stepu, x = -hf->sizex/2+px*stepx; i < hf->patch_sizex; i+=step, ofs+=step) {
	object3d_MultiTexCoord2f(0, u, v);
	object3d_MultiTexCoord2f(1, u, v);
	object3d_Vertex3f(x, z[ofs], y);
	object3d_MultiTexCoord2f(0, u, v-stepv);
	object3d_MultiTexCoord2f(1, u, v-stepv);
	object3d_Vertex3f(x, z[ofs+next_line], y+stepy);
	x += stepx;
	u += stepu;
      }
      object3d_MultiTexCoord2f(0, u-stepu, v);
      object3d_MultiTexCoord2f(1, u-stepu, v);
      object3d_Vertex3f(x-stepx, z[next_line+(ofs-step)], y+stepy);
      object3d_MultiTexCoord2f(0, px*stepu, v-stepv);
      object3d_MultiTexCoord2f(1, px*stepu, v-stepv);
      object3d_Vertex3f(-hf->sizex/2+px*stepx, z[(ofs-step*i)+next_line], y+stepy);
      ofs += next_line-hf->patch_sizex-(step-1);
      v -= stepv;
      y += stepy;
    }
    object3d_End();
    object3d_EndList();
  }

  return obj;
}

/*Transform (px,py) in patch unit coordinate and draw the corresponding patch*/
/*px=(x+S/2)*N/S */
/*where: N=number of patch on a row*/
/*       S=size of the bbox*/
static object3d *
create_mesh_patch_stripped_lod2(heightfield hf, float x, float y, int lod)
{
  int num_patch_x = (hf->w - 1)/(hf->patch_sizex - 1);
  int num_patch_y = (hf->h - 1)/(hf->patch_sizex - 1);
  int cellx = (int)((x+hf->sizex/2)*num_patch_x/hf->sizex);
  int celly = (int)((y+hf->sizey/2)*num_patch_y/hf->sizey);

  //printf("%d %d %f %f\n", cellx, celly, x, y);
  
  return create_mesh_patch_stripped_lod_list(hf, x, y, cellx, celly, lod);
}

static void
quadtree_fill(quadtree_node node, void  *hf)
{
  node->data = create_mesh_patch_stripped_lod2((heightfield)hf, node->box.corners[0].x, node->box.corners[0].y, 0);
}

static void
quadtree_set_material(quadtree_node node, void *mat)
{
  object3d_set_material((object3d *)node->data, (material)mat);
}
