#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <assert.h>

#include "stargl.h"

#include "object3d.h"

struct object3d {
  matrix4 local;
  matrix4 world;
  vertexbuffer vb;
  material mat;
};

object3d
object3d_create(matrix4 local, matrix4 world, vertexbuffer vb, material mat)
{
  object3d obj = malloc(sizeof(struct object3d));
  assert(obj);

  matrix4_copy(obj->world, world);
  matrix4_copy(obj->local, local);
  obj->vb = vb;
  obj->mat = mat;

  return obj;
}

void
object3d_set_material(object3d obj, material mat)
{
  obj->mat = mat;
}

void
object3d_to_opengl(object3d obj)
{
  assert(obj&&obj->vb);
  glPushMatrix();		/* Should be somewhere else in a loop */

  glMultMatrixd((double *)obj->world);
  glMultMatrixd((double *)obj->local);
  if(obj->mat)
    material_to_opengl(obj->mat);
  vertexbuffer_to_opengl(obj->vb);

  glPopMatrix();
}

void
object3d_destroy(object3d obj, DestroyFlag flag)
{
  if(flag&DESTROY_MAT)
    material_destroy(obj->mat);
  if(flag&DESTROY_VB)
    vertexbuffer_destroy(obj->vb);
  free(obj);
}

vertexbuffer
object3d_get_vertexbuffer(object3d obj)
{
  return obj->vb;
}

material
object3d_get_material(object3d obj)
{
  return obj->mat;
}

void
object3d_set_local_matrix(object3d obj, matrix4 local)
{
  matrix4_copy(obj->local, local);
}

void
object3d_set_world_matrix(object3d obj, matrix4 world)
{
  matrix4_copy(obj->world, world);
}

matrix4 *
object3d_get_local_matrix(object3d obj)
{
  return &obj->local;
}

matrix4 *
object3d_get_world_matrix(object3d obj)
{
  return &obj->world;
}
