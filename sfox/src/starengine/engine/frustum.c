#include <stdio.h>
#include "stargl.h"

#include "frustum.h"
#include "plan.h"
#include "mathengine.h"

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

  //  fprintf(stderr, "%f\n", ftm->left.d);
  fprintf(stderr, "LEFT from opengl %f ", ftm->left.d);
  vector3_print(&ftm->left.normal);
  fprintf(stderr, "RIGHT from opengl %f ", ftm->right.d);
  vector3_print(&ftm->right.normal);
  fprintf(stderr, "TOP from opengl %f ", ftm->top.d);
  vector3_print(&ftm->top.normal);
  fprintf(stderr, "BOTTOM from opengl %f ", ftm->bottom.d);
  vector3_print(&ftm->bottom.normal);
/*   fprintf(stderr, "FAR from opengl "); */
/*   vector3_print(&ftm->far.normal); */
  fprintf(stderr, "\n");
}

void
frustum_to_frustum2d(frustum2d *ftm2d, frustum *ftm)
{
  line2d_set(&ftm2d->left, ftm->left.normal.x, ftm->left.normal.z, ftm->left.d);
  line2d_set(&ftm2d->right, ftm->right.normal.x, ftm->right.normal.z, ftm->right.d);
  line2d_set(&ftm2d->front, ftm->far.normal.x, ftm->far.normal.z, ftm->far.d);
  line2d_set(&ftm2d->back, ftm->near.normal.x, ftm->near.normal.z, ftm->near.d);
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

/***********************************************************************/
/* Frustum2d functions                                                 */
/***********************************************************************/

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
