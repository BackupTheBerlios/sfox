#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "bbox.h"

void
bbox2d_set(bbox2d *bb, float tlx, float tly, float brx, float bry)
{
  assert(brx!=tlx&&bry!=tly);
  
  vector2_set(&bb->corners[0], tlx, tly);
  vector2_set(&bb->corners[1], tlx, bry);
  vector2_set(&bb->corners[2], brx, bry);
  vector2_set(&bb->corners[3], brx, tly);
}

unsigned int
bbox2d_width(bbox2d *bb)
{
  assert(bb->corners[3].x!=bb->corners[0].x);
  return abs(bb->corners[3].x-bb->corners[0].x);
}

unsigned int
bbox2d_height(bbox2d *bb)
{
  assert(bb->corners[0].y!=bb->corners[1].y);
  return abs(bb->corners[0].y-bb->corners[1].y);
}
