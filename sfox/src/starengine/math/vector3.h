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
  float x,y;
} vector2;

typedef struct vector3 {
  float x,y,z;
} vector3;

extern vector3 ZAXIS, YAXIS, XAXIS;

extern void vector2_set(vector2 *v, float x, float y);
extern INLINE void
vector2_copy(vector2 *dst, vector2 *src)
{
  memcpy(dst, src, sizeof(struct vector2));
}

extern void vector3_add(vector3 *dest, vector3 *v1, vector3 *v2);
extern void vector3_add_to(vector3 *v1, vector3 *v2);

extern void vector3_sub(vector3 *dest, vector3 *v2, vector3 *v3);
extern void vector3_sub_to(vector3 *v1, vector3 *v2);

extern void vector3_scale(vector3 *dest, vector3 *v, float k);
extern void vector3_scale_to(vector3 *v, float k);

extern void vector3_sub_scalar(vector3 *dest, vector3 *v, float k);
extern void vector3_sub_scalar_to(vector3 *v, float k);

extern void vector3_add_scalar(vector3 *dest, vector3 *v, float k);
extern void vector3_add_scalar_to(vector3 *v, float k);

extern float vector3_dot(vector3 *v1, vector3 *v2);
extern void vector3_cross(vector3 *dest, vector3 *v2, vector3 *v3);
extern float vector3_norm2(vector3 *v);
extern float vector3_norm(vector3 *v);
extern void vector3_normalise(vector3 *dest, vector3 *v);
extern void vector3_set(vector3 *v, float x, float y, float z);
extern void vector3_print(vector3 *v);

extern INLINE void
vector3_copy(vector3 *dst, vector3 *src)
{
  memcpy(dst, src, sizeof(struct vector3));
}

extern void vector3_mul_matrix4(vector3 *dest, vector3 *v, matrix4 m);

extern void matrix4_get_col(vector3 *dst, matrix4 m, unsigned int col);
extern void matrix4_get_row(vector3 *dst, matrix4 m, unsigned int row);

#endif
