#include <stdlib.h>
#include <assert.h>

#include "stargl.h"

#include "object2d.h"
#include "material.h"
#include "vertexbuffer.h"

struct object2d {
  matrix4 local;
  matrix4 world;
  material mat;

  vertexbuffer vb;
  double width, height;
};

/**********************************************************************/
/* Static declarations                                                */
/**********************************************************************/

/*Create a 1x1 quad*/
static vertexbuffer create_quad();

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

object2d
object2d_create(double sizex, double sizey, const matrix4 local, const matrix4 world, material mat)
{
  matrix4 scale;
  object2d obj = malloc(sizeof(struct object2d));
  assert(sizey>0||sizex>0);

  obj->vb = create_quad();

  obj->mat = mat;
  obj->width = sizex;
  obj->height = sizey;

  matrix4_copy(obj->world, world);
 /* Scale the 1x1 quad to sizex x sizey thanks to the local matrix */
  matrix4_to_scale(scale, sizex, sizey, 1);
  matrix4_mul(obj->local, local, scale);

  return obj;
}

void
object2d_to_opengl(object2d obj)
{
  assert(obj);
  glPushMatrix();

  glMultMatrixd((double *)obj->world);
  glMultMatrixd((double *)obj->local);
  if(obj->mat)
    material_to_opengl(obj->mat);
  vertexbuffer_to_opengl(obj->vb);

  glPopMatrix();
}

void
object2d_destroy(object2d obj)
{
  vertexbuffer_destroy(obj->vb);
  obj->vb = NULL;
  free(obj);
}

/************************************************************************/
/*Setter and getter                                                     */
/************************************************************************/
void
object2d_set_local_matrix(object2d obj, matrix4 local)
{
  matrix4_copy(obj->local, local);
}

void
object2d_set_world_matrix(object2d obj, matrix4 world)
{
  matrix4_copy(obj->world, world);
}

matrix4 *
object2d_get_local_matrix(object2d obj)
{
  return &obj->local;
}

matrix4 *
object2d_get_world_matrix(object2d obj)
{
  return &obj->world;
}


/***********************************************************************/
/* Static functions                                                    */
/***********************************************************************/

static vertexbuffer
create_quad()
{
  vertexbuffer vb = vertexbuffer_create(TRIANGLES_STRIP, 4, 0);

  vertexbuffer_lock(vb);
  {
    unsigned int i;
    vertex *vert = vertexbuffer_get_vertices(vb);
    
    vertex_set_coord(&vert[0], 0, 0, 0);
    vertex_set_coord(&vert[1], 0, 1, 0);
    vertex_set_coord(&vert[2], 1, 0, 0);
    vertex_set_coord(&vert[3], 1, 1, 0);

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
