#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>

/* m[row][col]*/

typedef float matrix4[4][4];

#define MATRIX4_IDENTITY \
  {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}
#define MATRIX4_ZERO \
  {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}

extern matrix4 matrix4_identity;
extern matrix4 matrix4_zero;

extern inline void matrix4_copy(matrix4 dst, matrix4 src);

extern inline void matrix4_to_identity(matrix4 dst);
extern inline void matrix4_to_scale(matrix4 dst, float sx, float sy, float sz);
extern inline void matrix4_to_rot_x(matrix4 dst, float a);
extern inline void matrix4_to_rot_y(matrix4 dst, float a);
extern inline void matrix4_to_rot_z(matrix4 dst, float a);
extern void matrix4_to_translate(matrix4 dst, float x, float y, float z);

extern void matrix4_transpose(matrix4 dst, matrix4 src);
extern void matrix4_mul(matrix4 dst, matrix4 a, matrix4 b);
extern void matrix4_mul_scalar(matrix4 m, float k);

/*semiorthogonal=translation+rotation, no scale(unity scale is ok)*/
extern void matrix4_semiorthogonal_get_inverse(matrix4 dst, matrix4 src);
extern void matrix4_semiorthogonal_to_inverse(matrix4 dst);

/*Use Cramer's rule*/
extern void matrix4_to_inverse(matrix4 m);
extern void matrix4_get_inverse(matrix4 dst, matrix4 src);

extern void matrix4_print(matrix4 m);

/*Some inlined functions */
extern void matrix4_to_zero(matrix4 m);
extern void matrix4_to_identity(matrix4 m);

#endif
