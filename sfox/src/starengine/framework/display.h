#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct display *display;

extern display display_create(const char *title, int resx, int resy,
                              int bpp, int fullscreen);
extern void display_destroy(display disp);

extern int display_height (display disp);
extern int display_width (display disp);

#endif
