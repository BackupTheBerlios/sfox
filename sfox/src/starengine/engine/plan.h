#ifndef PLAN9_H
#define PLAN9_H

#include "mathengine.h"

enum {PLFRONT=0, PLBACK, PLCOPLANAR, PLINTERSECT};

typedef struct {
  vector3 normal;
  double d;
} plane;

extern void plane_setv(plane *pl, vector3 *normal, double d);
extern void plane_set(plane *pl, double nx, double ny, double nz, double d);
extern void plane_normalize(plane *pl);

extern int plane_test_point(plane *pl, double x, double y, double z);
extern int plane_test_vector3(plane *pl, vector3 *v);

extern int plane_test_polygon(plane *pl, vector3 *point, unsigned int num);

#endif
