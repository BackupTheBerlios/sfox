#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "color.h"

color color_red = {1,0,0,0};

void
color_copy(color *dest, color *src)
{
  assert(dest&&src);
  memcpy(dest, src, sizeof(struct color));
}
