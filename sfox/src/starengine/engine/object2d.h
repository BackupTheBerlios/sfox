#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "matrix.h"
#include "material.h"
#include "vertexbuffer.h"

typedef struct object2d {
  matrix4 world;
  material mat;

  vertexbuffer vb;
  float width, height;
} object2d;

#define SF_OBJECT2D(x) ((object2d *)(x))

/* All object2d are simple quads of sizex x sizey with a material*/
extern object2d *object2d_create(float sizex, float sizey, matrix4 world, material mat);
extern void object2d_init(object2d *obj, float sizex, float sizey, matrix4 world, material mat);
extern void object2d_to_opengl(object2d *obj);
/*Doesn't free obj*/
extern void object2d_destroy(object2d *obj);
/*free obj*/
extern void object2d_free(object2d *obj);

/* All matrices are copied into object2d */
extern void object2d_set_world_matrix(object2d *obj, matrix4 world);
extern matrix4 *object2d_get_world_matrix(object2d *obj);

extern float object2d_width(object2d *obj);
extern float object2d_height(object2d *obj);

#endif
