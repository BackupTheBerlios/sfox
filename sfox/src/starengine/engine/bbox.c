#include <stdlib.h>
#include <assert.h>

#include "bbox.h"

void
bbox2d_set(bbox2d *bb, double tlx, double tly, double brx, double bry)
{
  assert(brx>tlx&&bry<tly);
  
  vector2_set(&bb->corners[0], tlx, tly);
  vector2_set(&bb->corners[1], tlx, bry);
  vector2_set(&bb->corners[2], brx, bry);
  vector2_set(&bb->corners[3], brx, tly);
}

unsigned int
bbox2d_width(bbox2d *bb)
{
  assert(bb->corners[3].x>bb->corners[0].x);
  return bb->corners[3].x-bb->corners[0].x;
}

unsigned int
bbox2d_height(bbox2d *bb)
{
  assert(bb->corners[0].y>bb->corners[1].y);
  return bb->corners[0].y-bb->corners[1].y;
}
