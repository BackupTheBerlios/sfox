#include <stdlib.h>
#include <assert.h>

#include "plan.h"

void
plane_set(plane *pl, double nx, double ny, double nz, double d)
{
  pl->normal.x = nx;
  pl->normal.y = ny;
  pl->normal.z = nz;
  pl->d = d;
}

void
plane_setv(plane *pl, vector3 *normal, double d)
{
  vector3_copy(&pl->normal, normal);
  pl->d = d;
}

void
plane_normalize(plane *pl)
{
  double norm = vector3_norm(&pl->normal);
  assert(NOTZERO(norm));
  norm = 1.0/norm;

  pl->normal.x *= norm;
  pl->normal.y *= norm;
  pl->normal.z *= norm;
  pl->d *= norm;
}

int
plane_test_point(plane *pl, double x, double y, double z)
{
  double res = pl->normal.x*x+pl->normal.y*y+pl->normal.z*z+pl->d;

  if(res > EPSILON)
    return PLFRONT;
  else if(res < -EPSILON)
    return PLBACK;

  return PLCOPLANAR;
}

int
plane_test_vector3(plane *pl, vector3 *v)
{
  return plane_test_point(pl, v->x, v->y, v->z);
}

int
plane_test_polygon(plane *pl, vector3 *point, unsigned int num)
{
  unsigned int i;
  int all_front = 1, all_back = 1;

  for(i = 0; i < num; i++)
    switch(plane_test_vector3(pl, &point[i])) {
	case PLFRONT:
	  all_back = 0;
	  break;
	case PLBACK:
	  all_front = 0;
	  break;
	default:
	  break;
    }

  if(all_front&&!all_back)
    return PLFRONT;
  else if(all_back&&!all_front)
    return PLBACK;
  else if(!all_front&&!all_back)
    return PLINTERSECT;
  return PLCOPLANAR;
}
