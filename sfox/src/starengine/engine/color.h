#ifndef COLOR_H
#define COLOR_H

typedef struct color {
  double r;
  double g;
  double b;
  double a;
} color;

extern color color_red;

extern inline void color_copy(color *dest, color *src);

#endif
