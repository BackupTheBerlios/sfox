#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "matrix.h"
#include "mathmacro.h"

matrix4 matrix4_identity = MATRIX4_IDENTITY;
matrix4 matrix4_zero = MATRIX4_ZERO;

void
matrix4_to_scale(matrix4 dst, double sx, double sy, double sz)
{
  dst[0][0] = sx;
  dst[1][1] = sy;
  dst[2][2] = sz;
  dst[3][3] = 1;

  dst[0][1] = dst[0][2] = dst[0][3] = 0;
  dst[1][0] = dst[1][2] = dst[1][3] = 0;
  dst[2][0] = dst[2][1] = dst[2][3] = 0;
  dst[3][0] = dst[3][1] = dst[3][2] = 0;
}

void
matrix4_to_rot_x(matrix4 dst, double a)
{
  double c = cos(DEG2RAD(a));
  double s = sin(DEG2RAD(a));

  dst[0][0] = 1;
  dst[0][1] = 0;
  dst[0][2] = 0;
  dst[0][3] = 0;

  dst[1][0] = 0;
  dst[1][1] = c;
  dst[1][2] = s;
  dst[1][3] = 0;

  dst[2][0] = 0;
  dst[2][1] = -s;
  dst[2][2] = c;
  dst[2][3] = 0;

  dst[3][0] = 0;
  dst[3][1] = 0;
  dst[3][2] = 0;
  dst[3][3] = 1;
}

void
matrix4_to_rot_y(matrix4 dst, double a)
{
  double c = cos(DEG2RAD(a));
  double s = sin(DEG2RAD(a));

  dst[0][0] = c;
  dst[0][1] = 0;
  dst[0][2] = -s;
  dst[0][3] = 0;


  dst[1][0] = 0;
  dst[1][1] = 1;
  dst[1][2] = 0;
  dst[1][3] = 0;

  dst[2][0] = s;
  dst[2][1] = 0;
  dst[2][2] = c;
  dst[2][3] = 0;

  dst[3][0] = 0;
  dst[3][1] = 0;
  dst[3][2] = 0;
  dst[3][3] = 1;
}

void
matrix4_to_rot_z(matrix4 dst, double a)
{
  double c = cos(DEG2RAD(a));
  double s = sin(DEG2RAD(a));

  dst[0][0] = c;
  dst[0][1] = s;
  dst[0][2] = 0;
  dst[0][3] = 0;


  dst[1][0] = -s;
  dst[1][1] = c;
  dst[1][2] = 0;
  dst[1][3] = 0;

  dst[2][0] = 0;
  dst[2][1] = 0;
  dst[2][2] = 1;
  dst[2][3] = 0;

  dst[3][0] = 0;
  dst[3][1] = 0;
  dst[3][2] = 0;
  dst[3][3] = 1;
}

void
matrix4_to_translate(matrix4 dst, double x, double y, double z)
{
  dst[0][0] = 1;
  dst[0][1] = 0;
  dst[0][2] = 0;
  dst[0][3] = 0;

  dst[1][0] = 0;
  dst[1][1] = 1;
  dst[1][2] = 0;
  dst[1][3] = 0;

  dst[2][0] = 0;
  dst[2][1] = 0;
  dst[2][2] = 1;
  dst[2][3] = 0;

  dst[3][0] = x;
  dst[3][1] = y;
  dst[3][2] = z;
  dst[3][3] = 1;
}

void
matrix4_mul(matrix4 dst, matrix4 a, matrix4 b)
{
  matrix4 tmp;
  unsigned int i,j,k;

  for(i=0; i<4; i++)
    for(j=0;j<4;j++) {
      tmp[j][i] = 0;
      for(k=0; k <4; k++)
	tmp[j][i] += a[j][k]*b[k][i];
    }

  matrix4_copy(dst, tmp);
}

void
matrix4_mul_scalar(matrix4 m, double k)
{
  unsigned int i, j;

  for(j=0;j<4;j++)
    for(i=0; i<4; i++)
      m[j][i] *= k;
}

void
matrix4_print(matrix4 m)
{
  int i,j;
  for(j=0;j<4;j++) {
    printf("| ");
    for(i=0;i<4;i++)
      printf("%f ", m[j][i]);
    printf(" |\n");
  }
  printf("\n");
}

void
matrix4_semiorthogonal_get_inverse(matrix4 dst, matrix4 src)
{
  matrix4 tmp;

  tmp[0][0] = src[0][0];
  tmp[0][1] = src[1][0];
  tmp[0][2] = src[2][0];

  tmp[1][0] = src[0][1];
  tmp[1][1] = src[1][1];
  tmp[1][2] = src[2][1];

  tmp[2][0] = src[0][2];
  tmp[2][1] = src[1][2];
  tmp[2][2] = src[2][2];

  tmp[3][0] = -(src[3][0]*src[0][0]+src[3][1]*src[0][1]+src[3][2]*src[0][2]);
  tmp[3][1] = -(src[3][0]*src[1][0]+src[3][1]*src[1][1]+src[3][2]*src[1][2]);
  tmp[3][2] = -(src[3][0]*src[2][0]+src[3][1]*src[2][1]+src[3][2]*src[2][2]);

  tmp[0][3] = 0;
  tmp[1][3] = 0;
  tmp[2][3] = 0;
  tmp[3][3] = 1;

  matrix4_copy(dst, tmp);
}

void
matrix4_semiorthogonal_to_inverse(matrix4 dst)
{
  matrix4_semiorthogonal_get_inverse(dst, dst);
}

void
matrix4_transpose(matrix4 dst, matrix4 src)
{
  matrix4 tmp;
  int i;

  for(i=0;i<4;i++) {
    tmp[0][i] = src[i][0];
    tmp[1][i] = src[i][1];
    tmp[2][i] = src[i][2];
    tmp[3][i] = src[i][3];
  }
  matrix4_copy(dst, tmp);
}

/* Some parts come from ogre3d */
inline static double
minor4(matrix4 m, unsigned int r0, unsigned int r1, unsigned int r2,
       unsigned int c0, unsigned int c1, unsigned int c2)
{
  return m[r0][c0]*(m[r1][c1]*m[r2][c2]-m[r1][c2]*m[r2][c1])-
    m[r0][c1]*(m[r1][c0]*m[r2][c2]-m[r2][c0]*m[r1][c2])+
    m[r0][c2]*(m[r1][c0]*m[r2][c1]-m[r2][c0]*m[r1][c1]);
}

static void
adjoint4(matrix4 dst, matrix4 src)
{
  matrix4 tmp;
  
  tmp[0][0] =  minor4(src, 1, 2, 3, 1, 2, 3);
  tmp[0][1] = -minor4(src, 0, 2, 3, 1, 2, 3);
  tmp[0][2] =  minor4(src, 0, 1, 3, 1, 2, 3);
  tmp[0][3] = -minor4(src, 0, 1, 2, 1, 2, 3);

  tmp[1][0] = -minor4(src, 1, 2, 3, 0, 2, 3);
  tmp[1][1] =  minor4(src, 0, 2, 3, 0, 2, 3);
  tmp[1][2] = -minor4(src, 0, 1, 3, 0, 2, 3);
  tmp[1][3] =  minor4(src, 0, 1, 2, 0, 2, 3);

  tmp[2][0] =  minor4(src, 1, 2, 3, 0, 1, 3);
  tmp[2][1] = -minor4(src, 0, 2, 3, 0, 1, 3);
  tmp[2][2] =  minor4(src, 0, 1, 3, 0, 1, 3);
  tmp[2][3] = -minor4(src, 0, 1, 2, 0, 1, 3);

  tmp[3][0] = -minor4(src, 1, 2, 3, 0, 1, 2);
  tmp[3][1] =  minor4(src, 0, 2, 3, 0, 1, 2);
  tmp[3][2] = -minor4(src, 0, 1, 3, 0, 1, 2);
  tmp[3][3] =  minor4(src, 0, 1, 2, 0, 1, 2);

  matrix4_copy(dst, tmp);
}

inline double
matrix4_determinant(matrix4 m)
{
  return m[0][0] * minor4(m, 1, 2, 3, 1, 2, 3) -
    m[0][1] * minor4(m, 1, 2, 3, 0, 2, 3) +
    m[0][2] * minor4(m, 1, 2, 3, 0, 1, 3) -
    m[0][3] * minor4(m, 1, 2, 3, 0, 1, 2);
}

void
matrix4_to_inverse(matrix4 m)
{
  double det = matrix4_determinant(m);
  assert(NOTZERO(det)&&"This matrix is not inversible");

  adjoint4(m, m);
  matrix4_mul_scalar(m, 1.0/det);
}

void
matrix4_get_inverse(matrix4 dst, matrix4 src)
{
  matrix4_copy(dst, src);
  matrix4_to_inverse(dst);
}

void 
matrix4_copy(matrix4 dst, matrix4 src)
{
  memcpy(dst, src, sizeof(matrix4));
}

void
matrix4_to_zero(matrix4 m)
{
  matrix4_copy(m, matrix4_zero);
}

void
matrix4_to_identity(matrix4 m)
{
  matrix4_copy(m, matrix4_identity);
}
