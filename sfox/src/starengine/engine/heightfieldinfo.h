#ifndef HEIGHTFIELDINFO_H
#define HEIGHTFIELDINFO_H

#include "heightfield.h"
#include "camera.h"
#include "display.h"

typedef struct heightfieldinfo *heightfieldinfo;

extern heightfieldinfo heightfieldinfo_create(char *landmap, heightfield hf, camera cam, display disp, double sizex, double sizey);
extern void heightfieldinfo_to_opengl(heightfieldinfo hfi);
extern void heightfieldinfo_destroy(heightfieldinfo hfi);

#endif
