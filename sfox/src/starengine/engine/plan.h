#ifndef PLAN_H
#define PLAN_H

#include "mathengine.h"

enum {PLFRONT=0, PLBACK, PLCOPLANAR, PLINTERSECT};

typedef struct {
  vector3 normal;
  double d;
} plane;

inline void plane_set(plane *pl, double nx, double ny, double nz, double d);
inline void plane_normalize(plane *pl);

inline int plane_test_point(plane *pl, double x, double y, double z);
inline int plane_test_vector3(plane *pl, vector3 *v);

int plane_test_polygon(plane *pl, vector3 *point, unsigned int num);

#endif
