#ifndef SKYBOX_H
#define SKYBOX_H

#include "camera.h"

typedef struct skybox *skybox;

extern skybox skybox_create(camera cam, char *left, char *right, char *front, char *back, char *top, char *bottom, float sx);

extern void skybox_to_opengl(skybox sb);

#endif
