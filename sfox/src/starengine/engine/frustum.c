#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#undef far
#undef near
#endif /*_WIN32*/

#include <stdio.h>

#include "stargl.h"

#include "frustum.h"
#include "plan.h"
#include "mathengine.h"

void
frustum_copy(frustum *dst, frustum *src)
{
  plane_copy(&dst->far, &src->far);
  plane_copy(&dst->near, &src->near);
  plane_copy(&dst->top, &src->top);
  plane_copy(&dst->bottom, &src->bottom);
  plane_copy(&dst->left, &src->left);
  plane_copy(&dst->right, &src->right);
}

/* Mark Morley's tutorial on frustum culling */
void
frustum_get_from_opengl(frustum *ftm)
{
  matrix4 proj, model, clip;

  glGetDoublev(GL_PROJECTION_MATRIX, (double *)proj);
  glGetDoublev(GL_MODELVIEW_MATRIX, (double *)model);

  matrix4_mul(clip, model, proj);

   /* Extract the numbers for the RIGHT plane */
  plane_set(&ftm->right, clip[0][3] - clip[0][0], clip[1][3] - clip[1][0],
	    clip[2][3] - clip[2][0], clip[3][2] - clip[3][0]);

   /* Extract the numbers for the LEFT plane */
  plane_set(&ftm->left, clip[0][3] + clip[0][0], clip[1][3] + clip[1][0],
	    clip[2][3] + clip[2][0], clip[3][2] + clip[3][0]);

   /* Extract the BOTTOM plane */
  plane_set(&ftm->bottom, clip[0][3] + clip[0][1], clip[1][3] + clip[1][1],
	    clip[2][3] + clip[2][1], clip[3][2] + clip[3][1]);

   /* Extract the TOP plane */
  plane_set(&ftm->top, clip[0][3] - clip[0][1], clip[1][3] - clip[1][1],
	    clip[2][3] - clip[2][1], clip[3][2] - clip[3][1]);

   /* Extract the FAR plane */
  plane_set(&ftm->far, clip[0][3] - clip[0][2], clip[1][3] - clip[1][2],
	    clip[2][3] - clip[2][2], clip[3][3] - clip[3][2]);

   /* Extract the NEAR plane */
  plane_set(&ftm->near, clip[0][3] + clip[0][2], clip[1][3] + clip[1][2],
	    clip[2][3] + clip[2][2], clip[3][3] + clip[3][2]);

  plane_normalize(&ftm->near);
  plane_normalize(&ftm->far);
  plane_normalize(&ftm->top);
  plane_normalize(&ftm->bottom);
  plane_normalize(&ftm->left);
  plane_normalize(&ftm->right);

  fprintf(stderr, "OPENGL:\n");
  frustum_print(ftm);
  fprintf(stderr, "\n");
}

int
frustum_point_is_into(frustum *ftm, double x, double y, double z)
{
  if(plane_test_point(&ftm->right, x, y, z)==PLBACK)
    return 0;
  if(plane_test_point(&ftm->left, x, y, z)==PLBACK)
    return 0;
  if(plane_test_point(&ftm->top, x, y, z)==PLBACK)
    return 0;
  if(plane_test_point(&ftm->bottom, x, y, z)==PLBACK)
    return 0;
  if(plane_test_point(&ftm->far, x, y, z)==PLBACK)
    return 0;
  if(plane_test_point(&ftm->near, x, y, z)==PLBACK)
    return 0;

  return 1;
}

inline void
frustum_transform(frustum *ftm, matrix4 m, vector3 *pos)
{
  vector3 tmp;

  vector3_mul_matrix4(&ftm->far.normal, &ftm->far.normal, m);
  vector3_mul_matrix4(&ftm->near.normal, &ftm->near.normal, m);
  vector3_mul_matrix4(&ftm->top.normal, &ftm->top.normal, m);
  vector3_mul_matrix4(&ftm->bottom.normal, &ftm->bottom.normal, m);
  vector3_mul_matrix4(&ftm->left.normal, &ftm->left.normal, m);
  vector3_mul_matrix4(&ftm->right.normal, &ftm->right.normal, m);
  vector3_mul_matrix4(&tmp, pos, m);
  //  vector3_print(&tmp);

  ftm->top.d = -vector3_dot(&ftm->top.normal, &tmp);
  ftm->bottom.d = -vector3_dot(&ftm->bottom.normal, &tmp);
  ftm->near.d = -((vector3_dot(&ftm->near.normal, &tmp)+(2.0f/1000.0f)));
  ftm->far.d = -vector3_dot(&ftm->far.normal, &tmp)+(3000.0f/1000.0f);
  ftm->left.d = -vector3_dot(&ftm->left.normal, &tmp);
  ftm->right.d = -vector3_dot(&ftm->right.normal, &tmp);
}

void
frustum_transform_and_copy(frustum *dst, frustum *ftm, matrix4 m, vector3 *pos)
{
  frustum_copy(dst, ftm);
  frustum_transform(dst, m, pos);
}

void
frustum_print(frustum *ftm)
{
  fprintf(stderr, "LEFT: ");
  plane_print(&ftm->left);
  fprintf(stderr, "RIGHT: ");
  plane_print(&ftm->right);
  fprintf(stderr, "TOP: ");
  plane_print(&ftm->top);
  fprintf(stderr, "BOTTOM: ");
  plane_print(&ftm->bottom);
  fprintf(stderr, "FAR: ");
  plane_print(&ftm->far);
  fprintf(stderr, "NEAR: ");
  plane_print(&ftm->near);
}

/***********************************************************************/
/* Frustum2d functions                                                 */
/***********************************************************************/

void
frustum_to_frustum2d(frustum2d *ftm2d, frustum *ftm)
{
  line2d_set(&ftm2d->left, ftm->left.normal.x, ftm->left.normal.y, ftm->left.d);
  line2d_set(&ftm2d->right, ftm->right.normal.x, ftm->right.normal.y, ftm->right.d);
  line2d_set(&ftm2d->front, ftm->far.normal.x, ftm->far.normal.y, ftm->far.d);
  line2d_set(&ftm2d->back, ftm->near.normal.x, ftm->near.normal.y, ftm->near.d);
}

int
frustum2d_point_is_into(frustum2d *ftm, double x, double y)
{
  if(line2d_test_point(&ftm->right, x, y)==LBACK)
    return 0;
  if(line2d_test_point(&ftm->left, x, y)==LBACK)
    return 0;
  if(line2d_test_point(&ftm->front, x, y)==LBACK)
    return 0;
  if(line2d_test_point(&ftm->back, x, y)==LBACK)
    return 0;

  return 1;
}

int
frustum2d_bbox_is_into(frustum2d *ftm, bbox2d *bb)
{
  if(line2d_test_bbox(&ftm->right, bb)==LBACK)
    return 0;
  if(line2d_test_bbox(&ftm->left, bb)==LBACK)
    return 0;
  if(line2d_test_bbox(&ftm->front, bb)==LBACK)
    return 0;
  if(line2d_test_bbox(&ftm->back, bb)==LBACK)
    return 0;

  return 1;
}
