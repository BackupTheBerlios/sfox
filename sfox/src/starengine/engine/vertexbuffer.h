#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "vertex.h"

typedef enum {TRIANGLES_INDEXED = 0, TRIANGLES_STRIP} vertexbuffer_type;

typedef struct vertexbuffer *vertexbuffer;


extern vertexbuffer vertexbuffer_create(vertexbuffer_type type, int num_vertices, int num_indices);
extern void vertexbuffer_destroy(vertexbuffer vb);

/* 1 unlock by lock*/
extern void vertexbuffer_lock(vertexbuffer vb);
extern void vertexbuffer_unlock(vertexbuffer vb);

/* VB must be locked before getting */
extern vertex *vertexbuffer_get_vertices(vertexbuffer vb);
extern int * vertexbuffer_get_indices(vertexbuffer vb);

extern unsigned int vertexbuffer_get_num_indices(vertexbuffer vb);
extern unsigned int vertexbuffer_get_num_vertices(vertexbuffer vb);

extern void vertexbuffer_to_opengl(vertexbuffer vb);


#endif
