#ifndef BBOX_H
#define BBOX_H

#include "mathengine.h"

/* corner 0 is top left, going CCW */
typedef struct bbox2d {
  vector2 corners[4];
} bbox2d;

/*tl=top left br=bottom right*/
extern void bbox2d_set(bbox2d *bb, double tlx, double tly, double brx, double bry);
extern unsigned int bbox2d_width(bbox2d *bb);
extern unsigned int bbox2d_height(bbox2d *bb);

#endif
