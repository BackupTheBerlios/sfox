#ifndef PLAN9_H
#define PLAN9_H

#include "mathengine.h"

enum {PLFRONT=0, PLBACK, PLCOPLANAR, PLINTERSECT};

typedef struct {
  vector3 normal;
  float d;
} plane;

extern void plane_setv(plane *pl, vector3 *normal, float d);
extern void plane_set(plane *pl, float nx, float ny, float nz, float d);
extern void plane_copy(plane *dst, plane *src);
extern void plane_normalize(plane *pl);

extern int plane_test_point(plane *pl, float x, float y, float z);
extern int plane_test_vector3(plane *pl, vector3 *v);

extern int plane_test_polygon(plane *pl, vector3 *point, unsigned int num);

extern void plane_print(plane *pl);

#endif
