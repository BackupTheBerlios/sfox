#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "vertexbuffer.h"
#include "matrix.h"
#include "material.h"

typedef enum {DESTROY_ALL=0xFF, DESTROY_MAT=2, DESTROY_VB=4} DestroyFlag;

typedef struct object3d *object3d;

/* loc is copied into object, vb,mat are pointers*/
extern object3d object3d_create(matrix4 local, matrix4 world, vertexbuffer vb, material mat);
extern void object3d_destroy(object3d obj, DestroyFlag flag);

extern void object3d_to_opengl(object3d obj);

extern void object3d_set_material(object3d obj, material mat);
extern material object3d_get_material(object3d obj);

extern vertexbuffer object3d_get_vertexbuffer(object3d obj);

/* All matrices are copied into object3d */
extern void object3d_set_local_matrix(object3d obj, matrix4 local);
extern void object3d_set_world_matrix(object3d obj, matrix4 world);
extern matrix4 *object3d_get_local_matrix(object3d obj);
extern matrix4 *object3d_get_world_matrix(object3d obj);

#endif
