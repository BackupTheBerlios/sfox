#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "matrix.h"
#include "material.h"

typedef struct object2d *object2d;

/* All object2d are simple quads of sizex x sizey with a material*/
extern object2d object2d_create(double sizex, double sizey, const matrix4 local, const matrix4 world, material mat);
extern void object2d_to_opengl(object2d obj);
extern void object2d_destroy(object2d obj);

/* All matrices are copied into object2d */
extern void object2d_set_local_matrix(object2d obj, matrix4 local);
extern void object2d_set_world_matrix(object2d obj, matrix4 world);
extern matrix4 *object2d_get_local_matrix(object2d obj);
extern matrix4 *object2d_get_world_matrix(object2d obj);

#endif
