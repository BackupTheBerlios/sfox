#include "vertex.h"

void
vertex_set_coord(vertex *v, double x, double y, double z)
{
  v->coord.x = x;
  v->coord.y = y;
  v->coord.z = z;
}

void
vertex_set_color(vertex *v, double r, double g, double b, double a)
{
  v->col.r = r;
  v->col.g = g;
  v->col.b = b;
  v->col.a = a;
}

void
vertex_set_tcoord(vertex *vx, int n, double u, double v)
{
  vx->tcoord[n].x = u;
  vx->tcoord[n].y = v;
}

void
vertex_copy(vertex *dest, vertex *src)
{
  memcpy(dest, src, sizeof(struct vertex));
}
