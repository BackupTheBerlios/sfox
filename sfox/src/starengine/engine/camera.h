#ifndef CAMERA_H
#define CAMERA_H

#include "mathengine.h"
#include "viewport.h"
#include "frustum.h"

typedef struct camera {
  vector3 look_at;
  vector3 up;
  vector3 pos;
  frustum ftm;                  /* Initialised in camera_to_opengl */
} *camera;

extern camera camera_create(double fov, double zfar, double znear, vector3 *pos, vector3 *look_at, vector3 *up, viewport vp);
/* Destroy the viewport */
extern void camera_destroy(camera cam);
extern void camera_to_opengl(camera cam);

extern void camera_set_look_at(camera cam, vector3 *look_at);
extern void camera_set_pos(camera cam, double x, double y, double z);

/*Function for fps-like camera */

/* Rotate the camera of xrel and yrel radians around x and y axes*/
extern void camera_mouse_move(camera cam, double xrel, double yrel);
/* Move the camera in the view direction at speed speed*/
extern void camera_move_along_view(camera cam, double speed);
/*Strafe*/
extern void camera_side_move(camera cam, double speed);
/* We stop moving the view up or down at angle angle (in DEG) */
extern void camera_set_max_theta(camera cam, double angle);

#endif
