#ifndef OBJECT_FACTORY
#define OBJECT_FACTORY

#include "object3d.h"

typedef enum {CUBE} ObjType;

extern object3d *object_factory_create(ObjType type, float size);

/* subdiv_x=number of horizontal quads subdiv_y=vertical quads */
extern object3d *create_plan_xy(float sizex, float sizey, int subdiv_x, int subdiv_y);

#endif
