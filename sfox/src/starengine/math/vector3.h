#ifndef VECTOR3_H
#define VECTOR3_H

#include <string.h>

#include "matrix.h"

#ifdef __GNUC__
#define INLINE __inline__
#endif
#ifndef INLINE
#define INLINE
#endif

typedef struct vector2 {
  double x,y;
} vector2;

typedef struct vector3 {
  double x,y,z;
} vector3;

extern vector3 ZAXIS, YAXIS, XAXIS;

extern void vector2_set(vector2 *v, double x, double y);
extern INLINE void
vector2_copy(vector2 *dst, vector2 *src)
{
  memcpy(dst, src, sizeof(struct vector2));
}

extern void vector3_add(vector3 *v1, vector3 *v2, vector3 *v3);
extern void vector3_scale(vector3 *dest, vector3 *v1, double k);
extern void vector3_sub(vector3 *v1, vector3 *v2, vector3 *v3);
extern void vector3_sub_scalar(vector3 *v1, vector3 *v2, double k);
extern void vector3_add_scalar(vector3 *v1, vector3 *v2, double k);
extern double vector3_dot(vector3 *v1, vector3 *v2);
extern void vector3_cross(vector3 *v1, vector3 *v2, vector3 *v3);
extern double vector3_norm2(vector3 *v1);
extern double vector3_norm(vector3 *v1);
extern void vector3_normalise(vector3 *dest, vector3 *v);
extern void vector3_set(vector3 *v1, double x, double y, double z);
extern void vector3_print(vector3 *v);

extern INLINE void
vector3_copy(vector3 *dst, vector3 *src)
{
  memcpy(dst, src, sizeof(struct vector3));
}

extern void vector3_mul_matrix4(vector3 *dest, vector3 *v, matrix4 m);

#endif
