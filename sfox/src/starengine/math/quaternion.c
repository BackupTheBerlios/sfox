#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "mathmacro.h"
#include "quaternion.h"

void
quaternion_set(quaternion *q, double x, double y, double z, double w)
{
  q->x = x;
  q->y = y;
  q->z = z;
  q->w = w;
}

void
quaternion_to_identity(quaternion *q)
{
  q->x = 0;
  q->y = 0;
  q->z = 0;
  q->w = 1;
}

void
quaternion_copy(quaternion *dest, const quaternion *src)
{
  dest->x = src->x;
  dest->y = src->y;
  dest->z = src->z;
  dest->w = src->w;
}

void
quaternion_from_axis_angle(quaternion *q, double ax, double ay, double az, double theta)
{
  if(NOTZERO(ax)||NOTZERO(ay)||NOTZERO(az)) {
    double c, s;

    theta /= 2.0;
    s = sin(theta);
    c = cos(theta);

    q->x = ax*s;
    q->y = ay*s;
    q->z = az*s;
    q->w = c;
  } else {
    q->x = q->y = q->z = 0;	/* Axis is vector 0 so identity quaternion */
    q->w = 1.0;
  }
}

void
quaternion_from_axis_anglev(quaternion *q, vector3 *axis, double theta)
{
  quaternion_from_axis_angle(q, axis->x, axis->y, axis->z, theta);
}

void
quaternion_from_euler(quaternion *q, double rotx, double roty, double rotz)
{
  quaternion q1, q2, q3;

  quaternion_from_axis_angle(&q1, 1, 0, 0, rotx);
  quaternion_from_axis_angle(&q2, 0, 1, 0, roty);
  quaternion_from_axis_angle(&q3, 0, 0, 1, rotz);

  quaternion_mul(q, &q1, &q2);
  quaternion_mul(q, q, &q3);
}

double
quaternion_norm(const quaternion *q)
{
  return sqrt(q->w*q->w+q->x*q->x+q->y*q->y+q->z*q->z);
}

double
quaternion_norm2(const quaternion *q)
{
  return q->w*q->w+q->x*q->x+q->y*q->y+q->z*q->z;
}

void
quaternion_div(quaternion *dest, const quaternion *q, double k)
{
  assert(NOTZERO(k));
  dest->x = q->x / k;
  dest->y = q->y / k;
  dest->z = q->z / k;
  dest->w = q->w / k;
}

/* w = w1w2 - x1x2 - y1y2 - z1z2 */
/* x = w1x2 + x1w2 + y1z2 - z1y2 */
/* y = w1y2 + y1w2 + z1x2 - x1z2 */
/* z = w1z2 + z1w2 + x1y2 - y1x2  */
void
quaternion_mul(quaternion *dest, const quaternion *q1, const quaternion *q2)
{
  quaternion tmp;

  tmp.w = q1->w*q2->w - q1->x*q2->x - q1->y*q2->y - q1->z*q2->z;
  tmp.x = q1->w*q2->x + q1->x*q2->w + q1->y*q2->z - q1->z*q2->y;
  tmp.y = q1->w*q2->y - q1->x*q2->z + q1->y*q2->w + q1->z*q2->x;
  tmp.z = q1->w*q2->z + q1->x*q2->y - q1->y*q2->x + q1->z*q2->w;

  quaternion_copy(dest, &tmp);
}

void
quaternion_normalize(quaternion *dest, const quaternion *q)
{
  quaternion_div(dest, q, quaternion_norm(q));
}

void
quaternion_to_matrix(matrix4 m, const quaternion *q)
{
  double x=q->x;
  double y=q->y;
  double z=q->z;
  double w=q->w;
  double x2=x*x;
  double y2=y*y;
  double z2=z*z;
  
  m[0][0] = 1 - 2*y2 - 2*z2;
  m[0][1] = 2*x*y - 2*w*z;
  m[0][2] = 2*x*z + 2*w*y;
  m[1][0] = 2*x*y + 2*w*z;
  m[1][1] = 1 - 2*x2 - 2*z2;
  m[1][2] = 2*y*z - 2*w*x;
  m[2][0] = 2*x*z - 2*w*y;
  m[2][1] = 2*y*z + 2*w*x;
  m[2][2] = 1 - 2*x2 - 2*y2;
  m[3][0] = m[3][1] = m[3][2] = m[0][3] = m[1][3] = m[2][3] = 0;
  m[3][3] = 1;  
}

void
quaternion_to_axis_angle(quaternion *q, double *ax, double *ay, double *az, double *theta)
{
  double scale = sqrt(q->x*q->x+q->y*q->y+q->z*q->z);
  if(NOTZERO(scale)) {
    *theta = 2*acos(q->w);
    *ax = q->x/scale;
    *ay = q->y/scale;
    *az = q->z/scale;
  } else {
    *theta = 0;
    *ax = 1;			/* Identity  */
    *ay = 0;
    *az = 0;
  }
}

void
quaternion_conjugate(quaternion *dest, const quaternion *q)
{
  dest->x = -q->x;
  dest->y = -q->y;
  dest->z = -q->z;
  dest->w = q->w;
}

void
quaternion_rotate_vector(vector3 *dest, const quaternion *q, const vector3 *v)
{
  quaternion p, conj, tmp;

  quaternion_copy(&tmp, q);
  quaternion_set(&p, v->x, v->y, v->z, 0);
  quaternion_conjugate(&conj, q);
  quaternion_mul(&tmp, q, &p);
  quaternion_mul(&tmp, &tmp, &conj);

  dest->x = tmp.x;
  dest->y = tmp.y;
  dest->z = tmp.z;
}

/* void */
/* quaternion_to_matrix(matrix4 dest, quaternion *q) */
/* { */
/*   dest[0][0] = q->w*q->w+q->x*q->x-q->y*q->y-q->z*q->z; */
/*   dest[0][1] = 2*q->x*q->y - 2*q->w*q->z; */
/*   dest[0][2] = 2*q->x*q->z + 2*q->w*q->y; */

/*   dest[1][0] = 2*q->x*q->y + 2*q->w*q->z; */
/*   dest[1][1] = q->w*q->w-q->x2+q->y*q->y-q->z*q->z; */
/*   dest[1][2] = 2*q->yq->z - 2*q->wq->x; */

/*   dest[2][0] = 2*q->xq->z - 2*q->wq->y; */
/*   dest[2][1] = 2*q->yq->z + 2*q->wq->x; */
/*   dest[2][2] = q->w*q->w-q->x2-q->y*q->y+q->z*q->z; */
/* } */
