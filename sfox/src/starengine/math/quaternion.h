#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3.h"
#include "matrix.h"

typedef struct {
  double x;
  double y;
  double z;
  double w;
} quaternion;

#define QUATERNION_IDENTITY \
  {0,0,0,1}

extern void quaternion_set(quaternion *q, double x, double y, double z, double w);
extern void quaternion_copy(quaternion *dest, const quaternion *src);
extern void quaternion_to_identity(quaternion *q);

/* Create a quaternion for an unit axis and an angle*/
extern void quaternion_from_axis_angle(quaternion *q, double ax, double ay, double az, double theta);

/* Create a quaternion from three angles*/
extern void quaternion_from_euler(quaternion *q, double rotx, double roty, double rotz);

extern void quaternion_div(quaternion *dest, const quaternion *q, double k);
extern void quaternion_mul(quaternion *dest, const quaternion *q1, const quaternion *q2);

extern void quaternion_normalize(quaternion *dest, const quaternion *q);
extern double quaternion_norm(const quaternion *q);
extern double quaternion_norm2(const quaternion *q);

/* Convert a UNIT quaternion into an agle and an axis */
extern void quaternion_to_matrix(matrix4 m, const quaternion *q);

/* Convert a quaternion into an agle and an axis */
extern void quaternion_to_axis_angle(quaternion *q, double *ax, double *ay, double *az, double *theta);

/* q must be an UNIT quaternnion*/
extern void quaternion_conjugate(quaternion *dest, const quaternion *q);
extern void quaternion_rotate_vector(vector3 *dest, const quaternion *q, const vector3 *v);

#endif
