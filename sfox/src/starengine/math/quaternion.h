#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3.h"
#include "matrix.h"

typedef struct {
  float x;
  float y;
  float z;
  float w;
} quaternion;

#define QUATERNION_IDENTITY \
  {0,0,0,1}

extern void quaternion_set(quaternion *q, float x, float y, float z, float w);
extern void quaternion_copy(quaternion *dest, const quaternion *src);
extern void quaternion_to_identity(quaternion *q);

/* Create a quaternion for an unit axis and an angle*/
extern void quaternion_from_axis_angle(quaternion *q, float ax, float ay, float az, float theta);
extern void quaternion_from_axis_anglev(quaternion *q, vector3 *axis, float theta);

/* Create a quaternion from three angles*/
extern void quaternion_from_euler(quaternion *q, float rotx, float roty, float rotz);

extern void quaternion_div(quaternion *dest, const quaternion *q, float k);
extern void quaternion_mul(quaternion *dest, const quaternion *q1, const quaternion *q2);
extern void quaternion_mul_to(quaternion *q1, const quaternion *q2);

extern void quaternion_normalize(quaternion *dest, const quaternion *q);
extern float quaternion_norm(const quaternion *q);
extern float quaternion_norm2(const quaternion *q);

/* Convert a UNIT quaternion into an agle and an axis */
extern void quaternion_to_matrix(matrix4 m, const quaternion *q);

/* Convert a quaternion into an agle and an axis */
extern void quaternion_to_axis_angle(quaternion *q, float *ax, float *ay, float *az, float *theta);

/* q must be an UNIT quaternnion*/
extern void quaternion_conjugate(quaternion *dest, const quaternion *q);
extern void quaternion_rotate_vector(vector3 *dest, const quaternion *q, const vector3 *v);

#endif
