#include "mathengine.h"
#include "line.h"

void
line2d_set(line2d *l, float nx, float ny, float d)
{
  vector2_set(&l->normal, nx, ny);
  l->d = d;
}

inline int
line2d_test_point(line2d *l, float x, float y)
{
  float res = l->normal.x*x+l->normal.y*y+l->d;

  if(res > EPSILON)
    return LFRONT;
  else if(res < -EPSILON)
    return LBACK;

  return LCOLLINEAR;
}

inline int
line2d_test_vector2(line2d *l, vector2 *v)
{
  return line2d_test_point(l, v->x, v->y);
}

int
line2d_test_polygon(line2d *l, vector2 *point, unsigned int num)
{
  unsigned int i;
  int all_front = 1, all_back = 1;

  for(i = 0; i < num; i++)
    switch(line2d_test_vector2(l, &point[i])) {
	case LFRONT:
	  all_back = 0;
	  break;
	case LBACK:
	  all_front = 0;
	  break;
	default:
	  break;
    }

  if(all_front&&!all_back)
    return LFRONT;
  else if(all_back&&!all_front)
    return LBACK;
  else if(!all_front&&!all_back)
    return LINTERSECT;
  return LCOLLINEAR;		/* A thin polygon */
}

int
line2d_test_bbox(line2d *l, bbox2d *bb)
{
  return line2d_test_polygon(l, bb->corners, 4);
}
