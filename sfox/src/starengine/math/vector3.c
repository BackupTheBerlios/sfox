#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "vector3.h"
#include "mathmacro.h"

vector3 ZAXIS = {0, 0, 1};
vector3 YAXIS = {0, 1, 0};
vector3 XAXIS = {1, 0, 0};

void
vector3_add(vector3 *dest, vector3 *v1, vector3 *v2)
{
  dest->x = v1->x+v2->x;
  dest->y = v1->y+v2->y;
  dest->z = v1->z+v2->z;
}

void
vector3_add_to(vector3 *v1, vector3 *v2)
{
  vector3_add(v1, v1, v2);
}

void
vector3_sub(vector3 *dest, vector3 *v1, vector3 *v2)
{
  dest->x = v1->x-v2->x;
  dest->y = v1->y-v2->y;
  dest->z = v1->z-v2->z;
}

void
vector3_sub_to(vector3 *v1, vector3 *v2)
{
  vector3_sub(v1, v1, v2);
}

void
vector3_sub_scalar(vector3 *dest, vector3 *v, float k)
{
  dest->x = v->x-k;
  dest->y = v->y-k;
  dest->z = v->z-k;
}

void
vector3_sub_scalar_to(vector3 *v1, float k)
{
  vector3_sub_scalar(v1, v1, k);
}

void
vector3_add_scalar(vector3 *dest, vector3 *v, float k)
{
  dest->x = v->x+k;
  dest->y = v->y+k;
  dest->z = v->z+k;
}

void
vector3_add_scalar_to(vector3 *v1, float k)
{
  vector3_add_scalar(v1, v1, k);
}

void
vector3_scale(vector3 *dest, vector3 *v, float k)
{
  dest->x = v->x*k;
  dest->y = v->y*k;
  dest->z = v->z*k;
}

void
vector3_scale_to(vector3 *v1, float k)
{
  vector3_scale(v1, v1, k);
}

float
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

float
vector3_norm2(vector3 *v1)
{
  return v1->x*v1->x+v1->y*v1->y+v1->z*v1->z;
}

float
vector3_norm(vector3 *v1)
{
  return sqrt(vector3_norm2(v1));
}

void
vector3_normalise(vector3 *dest, vector3 *v)
{
  float norm = vector3_norm(v);
  assert(NOTZERO(norm));
  vector3_scale(dest, v, 1.0/norm);
}

void
vector3_set(vector3 *v1, float x, float y, float z)
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
void vector2_set(vector2 *v, float x, float y)
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

void
matrix4_get_col(vector3 *dst, matrix4 m, unsigned int col)
{
  assert(col<4&&col>=0);
  dst->x = m[0][col];
  dst->y = m[1][col];
  dst->z = m[2][col];
}

void
matrix4_get_row(vector3 *dst, matrix4 m, unsigned int row)
{
  assert(row<4&&row>=0);
  dst->x = m[row][0];
  dst->y = m[row][1];
  dst->z = m[row][2];
}
