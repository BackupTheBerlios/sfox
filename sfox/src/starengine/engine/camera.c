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

#define DEFMAXSINTHETA 25

/*Bits for need_update*/
enum {UPDATE_ALL=0xFFFFFFFF, UPDATE_VIEW=1, UPDATE_PERSPECTIVE=2};

struct local_camera {
  vector3 look_at;
  vector3 up;
  vector3 pos;
  frustum ftm;                  /* Initialised in camera_to_opengl */

  viewport vp;
  double fov, znear, zfar;
  matrix4 view_matrix;
  matrix4 projection_matrix;

  unsigned int need_update;

  /*For fpslike camera*/
  double max_sin_theta;		/* Won't look up or down more than that */
};

/**********************************************************************/
/* Macros                                                             */
/**********************************************************************/

/*Macro for converting camera->local_camera*/
#define SF_LOCAL_CAMERA(x) ((struct local_camera *)(x))

/**********************************************************************/
/* Static declarations                                                */
/**********************************************************************/

static void update_view(struct local_camera *cam);
static void update_perspective(struct local_camera *cam);

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

camera
camera_create(double fov, double zfar, double znear, vector3 *pos, vector3 *look_at, vector3 *up, viewport vp)
{
  struct local_camera *cam = (struct local_camera *)malloc(sizeof(struct local_camera));
  assert(vp);

  cam->vp = vp;
  cam->fov = fov;
  cam->zfar = zfar;
  cam->znear = znear;

  vector3_copy(&cam->pos, pos);
  vector3_copy(&cam->up, up);
  vector3_copy(&cam->look_at, look_at);

  matrix4_to_zero(cam->projection_matrix);
  matrix4_to_identity(cam->view_matrix);
  cam->need_update = UPDATE_ALL;

  camera_set_max_theta((camera)cam, DEFMAXSINTHETA);

  return (camera)cam;
}

void
camera_destroy(camera cam)
{
  struct local_camera *lcam = SF_LOCAL_CAMERA(cam);
  viewport_destroy(lcam->vp);
  lcam->vp = NULL;
  free(lcam);
}

void
camera_to_opengl(camera cam)
{
  struct local_camera *lcam = SF_LOCAL_CAMERA(cam);
  viewport_to_opengl(lcam->vp);

  if(lcam->need_update&UPDATE_PERSPECTIVE) {
    update_perspective(lcam);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd((double *)lcam->projection_matrix);
    glMatrixMode(GL_MODELVIEW);
  }

  //if(lcam->need_update&UPDATE_VIEW) {
    update_view(lcam);
    glLoadMatrixd((double *)lcam->view_matrix);
    frustum_get_from_opengl(&cam->ftm);
    camera_update_frustum((camera)cam);
    //}
}

void
camera_set_look_at(camera cam, vector3 *look_at)
{
  SF_LOCAL_CAMERA(cam)->need_update |= UPDATE_VIEW;
  cam->look_at.x = look_at->x;
  cam->look_at.y = look_at->y;
  cam->look_at.z = look_at->z;
}

void
camera_set_pos(camera cam, double x, double y, double z)
{
  SF_LOCAL_CAMERA(cam)->need_update |= UPDATE_VIEW;
  cam->pos.x = x;
  cam->pos.y = y;
  cam->pos.z = z;
}

void
camera_update_frustum(camera cam)
{
  struct local_camera *lcam = SF_LOCAL_CAMERA(cam);
  vector3 L, D, U, tmp1, tmp2;
  vector3 *E = &lcam->pos;

  double tan_fov2 = tan(DEG2RAD(lcam->fov/2));
  double t = lcam->znear*tan_fov2;
  double b = -t;
  double r = t*viewport_ratio(lcam->vp);
  double l = -r;
  double near = -lcam->znear;
  double far = lcam->zfar;

  /* First we extract L D U vectors from view matrix */
  vector3_set(&D, lcam->view_matrix[0][2], lcam->view_matrix[1][2], lcam->view_matrix[2][2]);
  vector3_set(&U, lcam->view_matrix[0][1], lcam->view_matrix[1][1], lcam->view_matrix[2][1]);
  vector3_set(&L, lcam->view_matrix[0][0], lcam->view_matrix[1][0], lcam->view_matrix[2][0]);

  /*Far and Near planes*/
  {
    double d_dot_e = vector3_dot(&D, E);
    plane_setv(&lcam->ftm.far, &D, -(d_dot_e-far) );
    vector3_scale(&tmp1, &D, -1);
    plane_setv(&lcam->ftm.near, &tmp1, d_dot_e+near );
  }
  
  /* Left plane's normal = LN = normalise(near*L-right*D) */
  /* Left plane's distance = LN.E*/
  vector3_scale(&tmp1, &L, -near);
  vector3_scale(&tmp2, &D, l);
  vector3_add(&lcam->ftm.left.normal, &tmp1, &tmp2);
  /*vector3_scale(&lcam->ftm.left.normal, &lcam->ftm.left.normal, sqrt(near*near+r*r));*/
  vector3_normalise(&lcam->ftm.left.normal, &lcam->ftm.left.normal);
  lcam->ftm.left.d = -vector3_dot(&lcam->ftm.left.normal, E);

  /* Right plane's normal = RN = normalise(-right*D+near*L) */
  /* Right plane's distance = RN.E*/
  vector3_scale(&tmp1, &D, -r);
  vector3_scale(&tmp2, &L, -near);
  vector3_sub(&lcam->ftm.right.normal, &tmp1, &tmp2);
  vector3_normalise(&lcam->ftm.right.normal, &lcam->ftm.right.normal);
  lcam->ftm.right.d = -vector3_dot(&lcam->ftm.right.normal, E);

  /* Top plane's normal = RN = normalise(b*D-near*U) */
  /* Top plane's distance = RN.E*/
  vector3_scale(&tmp1, &D, b);
  vector3_scale(&tmp2, &U, -near);
  vector3_sub(&lcam->ftm.top.normal, &tmp1, &tmp2);
  vector3_normalise(&lcam->ftm.top.normal, &lcam->ftm.top.normal);
  lcam->ftm.top.d = -vector3_dot(&lcam->ftm.top.normal, E);

  /* Bottom plane's normal = RN = normalise(b*D+near*U) */
  /* Top plane's distance = RN.E*/
  vector3_scale(&tmp1, &D, b);
  vector3_scale(&tmp2, &U, -near);
  vector3_add(&lcam->ftm.bottom.normal, &tmp1, &tmp2);
  vector3_normalise(&lcam->ftm.bottom.normal, &lcam->ftm.bottom.normal);
  lcam->ftm.bottom.d = -vector3_dot(&lcam->ftm.bottom.normal, E);

  printf("CAMERA:\n");
  frustum_print(&lcam->ftm);
  printf("\n");
}

/***********************************************************************/
/* Functions for FPS-like camera                                       */
/***********************************************************************/


/* view is normalized because quaternion are faster with unit vector*/
/* view = look-pos           */
/* 2 quaterions are created: */
/*  -One for the rotation around the z local camera's axis(view^up) */
/*  -One for the rotation around the y local camera's axis(up)      */
/* Then they are multiplied and the view vector is rotated          */
/* Finally lookat = view + pos */
/* We test if the camera is looking too in the up or down direction: */
/* |cross(up,view)|=sin(up,view) and dot(up,view)=cos(up,view) */
/* sin>MAXTHETA is ok, otherwise*/
/*  if cos>0&&yrel>0 or  cos<0&&yrel<0 it's ok */
/* otherwise don't rotate around z */
void
camera_mouse_move(camera gcam, double xrel, double yrel)
{
  struct local_camera *cam = SF_LOCAL_CAMERA(gcam);
  quaternion q = QUATERNION_IDENTITY;
  quaternion q2;
  vector3 axis, view;
  double cos_theta, axis_norm;

  vector3_sub(&view, &cam->look_at, &cam->pos);
  vector3_normalise(&view, &view);
  vector3_cross(&axis, &view, &cam->up);

  axis_norm = vector3_norm(&axis); /* is also sin(view,up) */
  cos_theta = vector3_dot(&view, &cam->up);
  if( axis_norm>cam->max_sin_theta || (cos_theta>0&&yrel>0) ||
      (cos_theta<0&&yrel<0)) {
    vector3_scale(&axis, &axis, axis_norm);
    quaternion_from_axis_angle(&q, axis.x, axis.y, axis.z, -yrel);
  }
  quaternion_from_axis_angle(&q2, cam->up.x, cam->up.y, cam->up.z, -xrel);
  quaternion_mul(&q, &q, &q2);	/* Combine the two rotations */
  quaternion_rotate_vector(&view, &q, &view);

  vector3_add(&cam->look_at, &view, &cam->pos);

  cam->need_update |= UPDATE_VIEW;
}

void
camera_move_along_view(camera cam, double speed)
{
  vector3 tmp, view;

  vector3_sub(&view, &cam->look_at, &cam->pos);
  vector3_normalise(&view, &view);
  vector3_scale(&tmp, &view, speed);
  vector3_add(&cam->pos, &cam->pos, &tmp);
  vector3_add(&cam->look_at, &cam->look_at, &tmp);

  SF_LOCAL_CAMERA(cam)->need_update |= UPDATE_VIEW;
}

void
camera_side_move(camera cam, double speed)
{
  vector3 view, axis;

  vector3_sub(&view, &cam->look_at, &cam->pos);
  vector3_normalise(&view, &view);
  vector3_cross(&axis, &view, &cam->up);

  vector3_scale(&axis, &axis, speed/vector3_norm(&axis)); /* Normalise&move */
  vector3_add(&cam->pos, &cam->pos, &axis);
  vector3_add(&cam->look_at, &cam->look_at, &axis);

  SF_LOCAL_CAMERA(cam)->need_update |= UPDATE_VIEW;
}

void
camera_set_max_theta(camera cam, double angle)
{
  assert(angle<90&&angle>0);
  SF_LOCAL_CAMERA(cam)->max_sin_theta = sin(DEG2RAD(angle));
}

/**************************************/

/*view_matrix is supposed to be identity*/
/*Matrix from GLU*/
static void
update_view(struct local_camera *cam)
{
  vector3 i, j, k;

  vector3_sub(&i, &cam->look_at, &cam->pos);
  vector3_normalise(&i, &i);

  vector3_cross(&k, &i, &cam->up);
  vector3_normalise(&k, &k);

  vector3_cross(&j, &k, &i);
  vector3_normalise(&j, &j);
 
  cam->view_matrix[0][0] = k.x;	/* Left vector*/
  cam->view_matrix[1][0] = k.y;
  cam->view_matrix[2][0] = k.z;

  cam->view_matrix[0][1] = j.x;	/* Up vector */
  cam->view_matrix[1][1] = j.y;
  cam->view_matrix[2][1] = j.z;

  cam->view_matrix[0][2] = -i.x; /* Direction vector */
  cam->view_matrix[1][2] = -i.y;
  cam->view_matrix[2][2] = -i.z;

  cam->view_matrix[3][0] = -vector3_dot(&k, &cam->pos);
  cam->view_matrix[3][1] = -vector3_dot(&j, &cam->pos);;
  cam->view_matrix[3][2] = vector3_dot(&i, &cam->pos);;

  cam->need_update &= ~UPDATE_VIEW;
}

/*projection_matrix is supposed to have been zeroed*/
/*Matrix from the red book*/
static void
update_perspective(struct local_camera *cam)
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
