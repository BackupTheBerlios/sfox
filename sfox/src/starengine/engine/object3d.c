#ifdef _WIN32
# include <windows.h>
# undef far
# undef near
# include <GL/gl.h>
# include "starglext.h"
#endif

#include <stdlib.h>
#include <assert.h>

#include "starengine.h"
#include "stargl.h"

#include "object3d.h"

/**********************************************************************/
/* Init and co                                                        */
/**********************************************************************/
object3d *
object3d_create(matrix4 world, vertexbuffer vb, material mat)
{
  object3d *obj = malloc(sizeof(struct object3d));
  object3d_init(obj, world, vb, mat);

  return obj;
}

void
object3d_init(object3d *obj, matrix4 world, vertexbuffer vb, material mat)
{
  matrix4_copy(obj->world, world);
  obj->vb = vb;
  obj->mat = mat;
}

void
object3d_destroy(object3d *obj, DestroyFlag flag)
{
  if(obj->vb == NULL)
    glDeleteLists(obj->list, 1);
  if(flag&DESTROY_MAT)
    material_destroy(obj->mat);
  if(flag&DESTROY_VB)
    vertexbuffer_destroy(obj->vb);
}

void
object3d_free(object3d *obj, DestroyFlag flag)
{
  object3d_destroy(obj, flag);
  free(obj);
}

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/
void
object3d_to_opengl(object3d *obj)
{
  if(!obj->vb)
    return;

  glPushMatrix();		/* Should be somewhere else in a loop */

  glMultMatrixf((float *)obj->world);
  if(obj->mat)
    material_to_opengl(obj->mat);
  
  vertexbuffer_to_opengl(obj->vb);

  glPopMatrix();
}

/************************************************************************/
/* Getters and Setters                                                  */
/************************************************************************/
void
object3d_set_material(object3d *obj, material mat)
{
  obj->mat = mat;
}

vertexbuffer
object3d_get_vertexbuffer(object3d *obj)
{
  return obj->vb;
}

material
object3d_get_material(object3d *obj)
{
  return obj->mat;
}

void
object3d_set_world_matrix(object3d *obj, matrix4 world)
{
  matrix4_copy(obj->world, world);
}

matrix4 *
object3d_get_world_matrix(object3d *obj)
{
  return &obj->world;
}
