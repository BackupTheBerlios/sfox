#ifndef STARENGINE_H
#define STARENGINE_H

#ifdef _WIN32
# include <windows.h>
# include <GL/gl.h>
# include "starglext.h"
#endif

#ifdef _WIN32
/*Multitexturing*/
extern PFNGLACTIVETEXTUREARBPROC	glActiveTexture;
extern PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTexture;
extern PFNGLMULTITEXCOORD2FPROC         glMultiTexCoord2f;

/*VBO*/
extern PFNGLBINDBUFFERARBPROC    glBindBufferARB;
extern PFNGLGENBUFFERSARBPROC    glGenBuffersARB;
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
extern PFNGLBUFFERDATAARBPROC    glBufferDataARB;
extern PFNGLMAPBUFFERARBPROC     glMapBufferARB;
extern PFNGLUNMAPBUFFERARBPROC   glUnmapBufferARB;

/*DXTC textures*/
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
#endif

extern int starengine_init();

#endif
