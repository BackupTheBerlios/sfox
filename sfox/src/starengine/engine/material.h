#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "texture.h"

enum { DIFFUSE=1, SPECULAR=2, TEXTURE=4, COLOR=8 };

typedef struct material *material;

/* col is copied into material, tex[] contains no more than MAX_TEXTURES tetures */
extern material material_create(texture tex[], int num_textures, color *col, float diffuse, float specular);

/*Create a material which is only a texture*/
extern material material_create_single_texture_from_file(char *filename);

extern void material_destroy(material mat);

extern void material_to_opengl(material mat);

extern texture material_get_texture(material mat, int num);

#endif
