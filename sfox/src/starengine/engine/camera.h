#ifndef CAMERA_H
#define CAMERA_H

#include "mathengine.h"
#include "viewport.h"
#include "frustum.h"

typedef struct camera {
  vector3 up;
  vector3 pos;
  quaternion orientation;
  matrix4 view_matrix;

  frustum ftm;                  /* Initialised in camera_to_opengl */
  viewport vp;
  double fov, znear, zfar;
  matrix4 projection_matrix;

  unsigned int need_update;

  float max_pitch, max_yaw, max_roll; /* Absolute max */
  float pitch, yaw, roll;
} *camera;

#define CAM_UNLIMITED -1

extern camera camera_create(double fov, double zfar, double znear, vector3 *pos, vector3 *up, viewport vp);
/* Destroy the viewport */
extern void camera_destroy(camera cam);
extern void camera_to_opengl(camera cam);

extern void camera_set_pos(camera cam, double x, double y, double z);

/*Function for fps-like camera */

/* Rotate the camera of xrel and yrel radians around x and y axes*/
extern void camera_mouse_move(camera cam, double xrel, double yrel);
/* Move the camera in the view direction at speed speed*/
extern void camera_move_along_view(camera cam, double speed);
/*Strafe*/
extern void camera_side_move(camera cam, double speed);

extern void camera_set_max_ypr(camera cam, float yaw, float pitch, float roll);

extern void camera_update_frustum(camera cam);

#endif
