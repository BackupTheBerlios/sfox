#ifndef HEIGHTFIELD_H
#define HEIGHTFIELD_H

#include "object3d.h"
#include "camera.h"

typedef struct heightfield *heightfield;

/*image size must be (2^n)+1 x (2^m)+1*/
extern heightfield heightfield_create_from_file(camera cam,
                                                char *heightmap_filename,
                                                float sizex, float sizey,
                                                float sizez);

extern void heightfield_set_textures_from_file(heightfield hf, char *land, char *details);
extern void heightfield_set_detail_scale(heightfield hf, float sx, float sy);

extern void heightfield_to_opengl(heightfield hf);

/*Common setters and getters*/
extern void heightfield_set_world_matrix(heightfield hf, matrix4 world);
extern matrix4 *heightfield_get_world_matrix(heightfield hf);

#endif
