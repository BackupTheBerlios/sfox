#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "display.h"

typedef void (*renderfunc)(void *object);

typedef struct scene *scene;

extern scene scene_create();
extern void scene_to_opengl(scene scn);
extern void scene_add_object(scene scn, void *object, renderfunc func, void *data);
extern void scene_add_object2d(scene scn, void *object, renderfunc func, void *data);

/*Needed for 3d rendering*/
extern void scene_set_camera(scene scn, camera cam);
/*Needed for 2d rendering*/
extern void scene_set_display(scene scn, display disp);



#endif
