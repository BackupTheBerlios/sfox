#ifdef _WIN32
#include <windows.h>
#undef near
#undef far
#endif /*_WIN32*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "stargl.h"
#include "starglu.h"

#include "camera.h"
#include "mathengine.h"

#define DEG360BOUND(x) (((x)>=360)?(x)-360:(((x)<=-360)?(x)+360:(x)))

/*Bits for need_update*/
enum {UPDATE_ALL=0xFFFFFFFF, UPDATE_VIEW=1, UPDATE_PERSPECTIVE=2};

/**********************************************************************/
/* Static declarations                                                */
/**********************************************************************/

static void update_view(camera cam);
static void update_perspective(camera cam);

inline static int pitch_not_max(camera cam, float pitch);
inline static int yaw_not_max(camera cam, float yaw);
inline static int roll_not_max(camera cam, float roll);

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

camera
camera_create(double fov, double zfar, double znear, vector3 *pos, vector3 *up, viewport vp)
{
  camera cam = (camera)malloc(sizeof(struct camera));
  assert(vp);

  cam->vp = vp;
  cam->fov = fov;
  cam->zfar = zfar;
  cam->znear = znear;

  cam->pitch = 0;
  cam->yaw = 0;
  cam->roll = 0;

  vector3_copy(&cam->pos, pos);
  vector3_copy(&cam->up, up);

  matrix4_to_zero(cam->projection_matrix);
  matrix4_to_identity(cam->view_matrix);
  cam->need_update = UPDATE_ALL;

  camera_set_max_ypr(cam, CAM_UNLIMITED, CAM_UNLIMITED, CAM_UNLIMITED);

  quaternion_set(&cam->orientation, 0, 0, 0, 1);

  return cam;
}

void
camera_destroy(camera cam)
{
  viewport_destroy(cam->vp);
  cam->vp = NULL;
  free(cam);
}

void
camera_to_opengl(camera cam)
{
  viewport_to_opengl(cam->vp);

  if(cam->need_update&UPDATE_PERSPECTIVE) {
    update_perspective(cam);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd((double *)cam->projection_matrix);
    glMatrixMode(GL_MODELVIEW);
  }

  if(cam->need_update&UPDATE_VIEW) {
    update_view(cam);
    glLoadMatrixd((double *)cam->view_matrix);
    frustum_get_from_opengl(&cam->ftm);
    camera_update_frustum(cam);
  }
}

void
camera_set_pos(camera cam, double x, double y, double z)
{
  cam->need_update |= UPDATE_VIEW;
  cam->pos.x = x;
  cam->pos.y = y;
  cam->pos.z = z;
}

void
camera_update_frustum(camera cam)
{
  vector3 L, D, U, tmp1, tmp2;
  vector3 *E = &cam->pos;

  double tan_fov2 = tan(DEG2RAD(cam->fov/2));
  double t = cam->znear*tan_fov2;
  double b = -t;
  double r = t*viewport_ratio(cam->vp);
  double l = -r;
  double near = -cam->znear;
  double far = cam->zfar;

  /* First we extract L D U vectors from view matrix */
  vector3_set(&D, cam->view_matrix[0][2], cam->view_matrix[1][2], cam->view_matrix[2][2]);
  vector3_set(&U, cam->view_matrix[0][1], cam->view_matrix[1][1], cam->view_matrix[2][1]);
  vector3_set(&L, cam->view_matrix[0][0], cam->view_matrix[1][0], cam->view_matrix[2][0]);

  /*Far and Near planes*/
  {
    double d_dot_e = vector3_dot(&D, E);
    plane_setv(&cam->ftm.far, &D, -(d_dot_e-far) );
    vector3_scale(&tmp1, &D, -1);
    plane_setv(&cam->ftm.near, &tmp1, d_dot_e+near );
  }
  
  /* Left plane's normal = LN = normalise(near*L-right*D) */
  /* Left plane's distance = LN.E*/
  vector3_scale(&tmp1, &L, -near);
  vector3_scale(&tmp2, &D, l);
  vector3_add(&cam->ftm.left.normal, &tmp1, &tmp2);
  /*vector3_scale(&cam->ftm.left.normal, &cam->ftm.left.normal, sqrt(near*near+r*r));*/
  vector3_normalise(&cam->ftm.left.normal, &cam->ftm.left.normal);
  cam->ftm.left.d = -vector3_dot(&cam->ftm.left.normal, E);

  /* Right plane's normal = RN = normalise(-right*D+near*L) */
  /* Right plane's distance = RN.E*/
  vector3_scale(&tmp1, &D, -r);
  vector3_scale(&tmp2, &L, -near);
  vector3_sub(&cam->ftm.right.normal, &tmp1, &tmp2);
  vector3_normalise(&cam->ftm.right.normal, &cam->ftm.right.normal);
  cam->ftm.right.d = -vector3_dot(&cam->ftm.right.normal, E);

  /* Top plane's normal = RN = normalise(b*D-near*U) */
  /* Top plane's distance = RN.E*/
  vector3_scale(&tmp1, &D, b);
  vector3_scale(&tmp2, &U, -near);
  vector3_sub(&cam->ftm.top.normal, &tmp1, &tmp2);
  vector3_normalise(&cam->ftm.top.normal, &cam->ftm.top.normal);
  cam->ftm.top.d = -vector3_dot(&cam->ftm.top.normal, E);

  /* Bottom plane's normal = RN = normalise(b*D+near*U) */
  /* Top plane's distance = RN.E*/
  vector3_scale(&tmp1, &D, b);
  vector3_scale(&tmp2, &U, -near);
  vector3_add(&cam->ftm.bottom.normal, &tmp1, &tmp2);
  vector3_normalise(&cam->ftm.bottom.normal, &cam->ftm.bottom.normal);
  cam->ftm.bottom.d = -vector3_dot(&cam->ftm.bottom.normal, E);

/*   printf("CAMERA:\n"); */
/*   frustum_print(&cam->ftm); */
/*   printf("\n"); */
}

/***********************************************************************/
/* Functions for FPS-like camera                                       */
/***********************************************************************/

/*Find the local X axis, create a rotation around this axe, then */
/*concat it with the current orientation */
/*Create a rotation around the up vector and concat*/
void
camera_mouse_move(camera cam, double xrel, double yrel)
{
  float pitch = cam->pitch+yrel;
  float yaw = cam->yaw+xrel;
  quaternion q;
  vector3 tmp;

  pitch = DEG360BOUND(pitch);
  yaw = DEG360BOUND(yaw);

  if(pitch_not_max(cam, pitch)) {
    cam->pitch = pitch;
    quaternion_rotate_vector(&tmp, &cam->orientation, &XAXIS);
    quaternion_from_axis_anglev(&q, &tmp, DEG2RAD(-yrel));
    quaternion_mul(&cam->orientation, &q, &cam->orientation);
  }

  if(yaw_not_max(cam, yaw)) {
    quaternion_from_axis_anglev(&q, &YAXIS, DEG2RAD(-xrel));
    quaternion_mul(&cam->orientation, &q, &cam->orientation);
  }

  cam->need_update |= UPDATE_VIEW;
}

void
camera_move_along_view(camera cam, double speed)
{
  vector3 view;

  vector3_set(&view, -cam->view_matrix[0][2], -cam->view_matrix[1][2], -cam->view_matrix[2][2]);
  vector3_scale(&view, &view, speed);
  vector3_add(&cam->pos, &cam->pos, &view);

  cam->need_update |= UPDATE_VIEW;
}

void
camera_side_move(camera cam, double speed)
{
  vector3 right;

  vector3_set(&right, speed*cam->view_matrix[0][0], speed*cam->view_matrix[1][0], speed*cam->view_matrix[2][0]);
  vector3_add(&cam->pos, &cam->pos, &right);

  cam->need_update |= UPDATE_VIEW;
}

void
camera_set_max_ypr(camera cam, float yaw, float pitch, float roll)
{
  cam->max_yaw = yaw;
  cam->max_pitch = pitch;
  cam->max_roll = roll;
}

/**************************************/

/*view_matrix is supposed to be identity*/
/*view_matrix is R U -D*/
static void
update_view(camera cam)
{
  quaternion_to_matrix(cam->view_matrix, &cam->orientation);

  cam->view_matrix[3][0] = -(cam->view_matrix[0][0]*cam->pos.x+cam->view_matrix[1][0]*cam->pos.y+cam->view_matrix[2][0]*cam->pos.z);
  cam->view_matrix[3][1] = -(cam->view_matrix[0][1]*cam->pos.x+cam->view_matrix[1][1]*cam->pos.y+cam->view_matrix[2][1]*cam->pos.z);
  cam->view_matrix[3][2] = -(cam->view_matrix[0][2]*cam->pos.x+cam->view_matrix[1][2]*cam->pos.y+cam->view_matrix[2][2]*cam->pos.z);

  matrix4_print(cam->view_matrix);

  cam->need_update &= ~UPDATE_VIEW;
}

/*projection_matrix is supposed to have been zeroed*/
/*Matrix from the red book*/
static void
update_perspective(camera cam)
{
  double fov2 = DEG2RAD(cam->fov/2);
  double x, y, z;
  double t,b,r,l;
  double near = cam->znear;
  double far = cam->zfar;
  double n2 = 2*near;

  assert(far!=near&&NOTZERO(far)&&NOTZERO(near));

  t = tan(fov2)*near;
  b = -t;
  r = viewport_ratio(cam->vp)*t;
  l = -r;

  x = 1.0/(r-l);
  y = 1.0/(t-b);
  z = 1.0/(far-near);
  
  cam->projection_matrix[0][0] = x*n2;
  cam->projection_matrix[2][0] = x*(r+l);

  cam->projection_matrix[1][1] = y*n2;
  cam->projection_matrix[2][1] = y*(t+b);

  cam->projection_matrix[2][2] = -z*(far+near);
  cam->projection_matrix[3][2] = -2*far*near*z;

  cam->projection_matrix[2][3] = -1;
    
  cam->need_update &= ~UPDATE_PERSPECTIVE;
}

inline static int
pitch_not_max(camera cam, float pitch)
{
  return cam->max_pitch == CAM_UNLIMITED || (pitch<cam->max_pitch && pitch>-cam->max_pitch);
}

inline static int
yaw_not_max(camera cam, float yaw)
{
  return cam->max_yaw == CAM_UNLIMITED || (yaw<cam->max_yaw && yaw>-cam->max_yaw);
}

inline static int
roll_not_max(camera cam, float roll)
{
  return cam->max_roll == CAM_UNLIMITED || (roll<cam->max_roll && roll>-cam->max_roll);
}
