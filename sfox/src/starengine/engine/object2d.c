#ifdef _WIN32
#include <windows.h>
#endif /*_WIN32*/
#include <stdlib.h>
#include <assert.h>

#include "stargl.h"

#include "object2d.h"
#include "material.h"
#include "vertexbuffer.h"

/**********************************************************************/
/* Static declarations                                                */
/**********************************************************************/

/*Create a sizexxsizey quad*/
static vertexbuffer create_quad(float sizex, float sizey);

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

object2d *
object2d_create(float sizex, float sizey, matrix4 world, material mat)
{
  object2d *obj = malloc(sizeof(struct object2d));
  object2d_init(obj, sizex, sizey, world, mat);
  
  return obj;
}

void
object2d_init(object2d *obj, float sizex, float sizey, matrix4 world, material mat)
{
  assert(sizey>0&&sizex>0);

  obj->vb = create_quad(sizex, sizey);
  obj->mat = mat;
  obj->width = sizex;
  obj->height = sizey;

  matrix4_copy(obj->world, world);
}

void
object2d_to_opengl(object2d *obj)
{
  assert(obj);
  glPushMatrix();

  glMultMatrixd((double *)obj->world);
  if(obj->mat)
    material_to_opengl(obj->mat);
  vertexbuffer_to_opengl(obj->vb);

  glPopMatrix();
}

void
object2d_destroy(object2d *obj)
{
  vertexbuffer_destroy(obj->vb);
  obj->vb = NULL;
}

void
object2d_free(object2d *obj)
{
  object2d_destroy(obj);
  free(obj);
}

/************************************************************************/
/*Setter and getter                                                     */
/************************************************************************/
void
object2d_set_world_matrix(object2d *obj, matrix4 world)
{
  matrix4_copy(obj->world, world);
}

matrix4 *
object2d_get_world_matrix(object2d *obj)
{
  return &obj->world;
}

float
object2d_width(object2d *obj)
{
  return obj->width;
}

float
object2d_height(object2d *obj)
{
  return obj->height;
}

/***********************************************************************/
/* Static functions                                                    */
/***********************************************************************/

static vertexbuffer
create_quad(float sizex, float sizey)
{
  vertexbuffer vb = vertexbuffer_create(VB_SYSTEM, TRIANGLES_STRIP, 4, 0);

  vertexbuffer_lock(vb);
  {
    unsigned int i;
    vertex *vert = vertexbuffer_get_vertices(vb);
    
    vertex_set_coord(&vert[0], 0, 0, 0);
    vertex_set_coord(&vert[1], 0, sizey, 0);
    vertex_set_coord(&vert[2], sizex, 0, 0);
    vertex_set_coord(&vert[3], sizex, sizey, 0);

    for(i = 0; i < MAX_TEXTURES; i++) {
      vertex_set_tcoord(&vert[0], i, 0, 0);
      vertex_set_tcoord(&vert[1], i, 0, 1);
      vertex_set_tcoord(&vert[2], i, 1, 0);
      vertex_set_tcoord(&vert[3], i, 1, 1);
    }
  }
  vertexbuffer_unlock(vb);
  
  return vb;
}
