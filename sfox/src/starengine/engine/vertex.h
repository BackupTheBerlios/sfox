#ifndef VERTEX_H
#define VERTEX_H

#include "engineconst.h"
#include "color.h"
#include "vector3.h"

/*Don't change the order(will break vertexbuffer.c) */
typedef struct vertex {
  vector3 coord;
  vector2 tcoord[MAX_TEXTURES];
  color col;
} vertex;

#define VERTEXOFFSETCOORD 0
#define VERTEXOFFSETTCOORD(i) (sizeof(vector3)+sizeof(vector2)*(i))
#define VERTEXOFFSETCOLOR (sizeof(vector3)+sizeof(vector2)*(MAX_TEXTURES))

extern void vertex_set_coord(vertex *v, float x, float y, float z);
extern void vertex_set_color(vertex *v, float r, float g, float b, float a);
/* Set texture coordinates for texture n*/
extern void vertex_set_tcoord(vertex *vx, int n, float u, float v);
extern void vertex_copy(vertex *dest, vertex *src);


#endif
