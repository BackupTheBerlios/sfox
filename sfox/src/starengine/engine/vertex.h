#ifndef VERTEX_H
#define VERTEX_H

#include "engineconst.h"
#include "color.h"
#include "vector3.h"

typedef struct vertex {
  vector3 coord;
  vector2 tcoord[MAX_TEXTURES];
  color col;
} vertex;

extern void vertex_set_coord(vertex *v, double x, double y, double z);
extern void vertex_set_color(vertex *v, double r, double g, double b, double a);
/* Set texture coordinates for texture n*/
extern void vertex_set_tcoord(vertex *vx, int n, double u, double v);
extern void vertex_copy(vertex *dest, vertex *src);


#endif
