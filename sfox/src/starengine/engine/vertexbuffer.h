/**
   A vertexbuffer contains an array of vertex.
*/
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "vertex.h"

typedef enum {VB_SYSTEM=0, VB_STATIC_DRAW, VB_DYNAMIC_DRAW, VB_LIST} vertexbuffer_type;
typedef enum {TRIANGLES_INDEXED = 0, TRIANGLES_STRIP} vertices_type;

typedef struct vertexbuffer *vertexbuffer;


extern vertexbuffer vertexbuffer_create(vertexbuffer_type vbtype, vertices_type vtype, int num_vertices, int num_indices);
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

extern void vertexbuffer_bind(vertexbuffer vb);

/*Warper around OpenGL direct mode for VB_LIST*/
extern void vertexbuffer_Begin(vertexbuffer vb, unsigned int type);
extern void vertexbuffer_End(vertexbuffer vb);
extern void vertexbuffer_MultiTexCoord2f(vertexbuffer vb, int texunit, float u, float v);
extern void vertexbuffer_TexCoord2f(vertexbuffer vb, float u, float v);
extern void vertexbuffer_Vertex3f(vertexbuffer vb, float x, float y, float z);


#endif
