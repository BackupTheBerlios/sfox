#ifndef VIEWPORT_H
#define VIEWPORT_H

typedef struct viewport *viewport;

extern viewport viewport_create(int x, int y, int width, int height);
extern void viewport_destroy(viewport vp);
extern float viewport_ratio(viewport vp);
extern void viewport_to_opengl(viewport vp);

#endif
