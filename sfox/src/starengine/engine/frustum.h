#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "bbox.h"
#include "line.h"
#include "plan.h"

/* all plane faces inward */
typedef struct {
  plane far;
  plane near;
  plane left;
  plane right;
  plane top;
  plane bottom;
} frustum;

/* all line faces inward */
typedef struct {
  line2d left;
  line2d right;
  line2d front;
  line2d back;
} frustum2d;

extern void frustum_get_from_opengl(frustum *ftm);
/*Project the frustum on the xz plane*/
extern void frustum_to_frustum2d(frustum2d *ftm2d, frustum *ftm);
extern int frustum_point_is_into(frustum *ftm, double x, double y, double z);

extern int frustum2d_point_is_into(frustum2d *ftm, double x, double y);
extern int frustum2d_bbox_is_into(frustum2d *ftm2d, bbox2d *bb);

#endif
