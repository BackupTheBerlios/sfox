#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "vector3.h"
#include "mathmacro.h"

void
vector3_add(vector3 *v1, vector3 *v2, vector3 *v3)
{
  v1->x = v2->x+v3->x;
  v1->y = v2->y+v3->y;
  v1->z = v2->z+v3->z;
}

void
vector3_sub(vector3 *v1, vector3 *v2, vector3 *v3)
{
  v1->x = v2->x-v3->x;
  v1->y = v2->y-v3->y;
  v1->z = v2->z-v3->z;
}

void
vector3_sub_scalar(vector3 *v1, vector3 *v2, double k)
{
  v1->x = v2->x-k;
  v1->y = v2->y-k;
  v1->z = v2->z-k;
}

void
vector3_add_scalar(vector3 *v1, vector3 *v2, double k)
{
  v1->x = v2->x+k;
  v1->y = v2->y+k;
  v1->z = v2->z+k;
}

void
vector3_scale(vector3 *dest, vector3 *v1, double k)
{
  dest->x = v1->x*k;
  dest->y = v1->y*k;
  dest->z = v1->z*k;
}

double
vector3_dot(vector3 *v1, vector3 *v2)
{
  return v1->x*v2->x+v1->y*v2->y+v1->z*v2->z;
}

void
vector3_cross(vector3 *v1, vector3 *v2, vector3 *v3)
{
  vector3 tmp;

  tmp.x = v2->y*v3->z-v2->z*v3->y;
  tmp.y = v2->z*v3->x-v2->x*v3->z;
  tmp.z = v2->x*v3->y-v2->y*v3->x;

  v1->x = tmp.x;
  v1->y = tmp.y;
  v1->z = tmp.z;
}

double
vector3_norm2(vector3 *v1)
{
  return v1->x*v1->x+v1->y*v1->y+v1->z*v1->z;
}

double
vector3_norm(vector3 *v1)
{
  return sqrt(vector3_norm2(v1));
}

void
vector3_normalise(vector3 *dest, vector3 *v)
{
  double norm = vector3_norm(v);
  assert(NOTZERO(norm));
  vector3_scale(dest, v, 1.0/norm);
}

void
vector3_set(vector3 *v1, double x, double y, double z)
{
  assert(v1);
  v1->x = x;
  v1->y = y;
  v1->z = z;
}

void
vector3_mul_matrix4(vector3 *dest, vector3 *v, matrix4 m)
{
  vector3 tmp;

  tmp.x = v->x*m[0][0]+v->y*m[1][0]+v->z*m[2][0]+m[3][0];
  tmp.y = v->x*m[0][1]+v->y*m[1][1]+v->z*m[2][1]+m[3][1];
  tmp.z = v->x*m[0][2]+v->y*m[1][2]+v->z*m[2][2]+m[3][2];

  dest->x = tmp.x;
  dest->y = tmp.y;
  dest->z = tmp.z;
}

void
vector3_print(vector3 *v)
{
  printf("<%f %f %f>\n", v->x, v->y, v->z);
}

/***********************************************************************/
/* Vector2                                                             */
/***********************************************************************/
void vector2_set(vector2 *v, double x, double y)
{
  v->x = x;
  v->y = y;
}

/***********************************************************************/
/* Inlined functions                                                   */
/***********************************************************************/
INLINE void
vector3_copy(vector3 *dst, vector3 *src)
{
  memcpy(dst, src, sizeof(struct vector3));
}

INLINE void
vector2_copy(vector2 *dst, vector2 *src)
{
  memcpy(dst, src, sizeof(struct vector2));
}
