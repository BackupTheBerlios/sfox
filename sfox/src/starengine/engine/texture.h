#ifndef TEXTURE_H
#define TEXTURE_H

#include "matrix.h"

typedef enum {CLAMP=0, CLAMP_TO_EDGE, REPEAT} clampmode;

typedef enum {NEAREST=0, LINEAR, NEAREST_MIPMAP, LINEAR_MIPMAP,
              NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
} filtermode;

typedef enum {RGB=0, RGBA, ALPHA} pixelfmt;

typedef enum {UNSIGNED_BYTE=0, UNSIGNED_INT} datatype;

typedef struct texture *texture;

extern texture texture_create_from_file(char *filename);
extern void texture_destroy(texture tex);

extern void texture_bind(texture tex);

/* Bind and execute all glTexEnv() queued in the list */
extern void texture_to_opengl(texture tex);

/* Add pname and its arg param to the list of glTexEnv() */
extern void texture_add_texture_env(texture tex, unsigned int pname, unsigned int param);

/* m is copied, default matrix is identity */
extern void texture_set_matrix(texture tex, matrix4 m);

/* Set clamp mode for S and T*/
extern void texture_set_st_clamp_mode(texture tex, clampmode mode);
/* Set min filter mode */
extern void texture_set_min_filter_mode(texture tex, filtermode mode);
/* Set mag filter mode */
extern void texture_set_mag_filter_mode(texture tex, filtermode mode);

/* Put the image whose size is width*height at (offsetx,offsety)  */
extern void texture_copy_from_image(texture tex, void *pixels,
                                    int offsetx, int offsety,
                                    unsigned int width, unsigned int height,
                                    pixelfmt pix_format, datatype data_type);

#endif
