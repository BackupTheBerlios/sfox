#ifndef COLOR_H
#define COLOR_H

typedef struct color {
  float r;
  float g;
  float b;
  float a;
} color;

extern color color_red;

extern inline void color_copy(color *dest, color *src);

#endif
