#ifdef _WIN32
# include <windows.h>
#include <GL/glaux.h>
#endif

#include "stargl.h"
#include "starglu.h"
#include "starglext.h"

#include "starengine.h"

#ifdef _WIN32
PFNGLACTIVETEXTUREARBPROC	glActiveTexture;
PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTexture;
PFNGLBINDBUFFERARBPROC glBindBufferARB;
PFNGLGENBUFFERSARBPROC glGenBuffersARB;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
PFNGLBUFFERDATAARBPROC glBufferDataARB;
PFNGLMAPBUFFERARBPROC glMapBufferARB;
PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
#endif

int
starengine_init()
{
#ifdef _WIN32
  glActiveTexture = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTexture");
  glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTexture");
  glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
  glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
  glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
  glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
  glMapBufferARB = (PFNGLMAPBUFFERARBPROC) wglGetProcAddress("glMapBufferARB");
  glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB");
  glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) wglGetProcAddress("glCompressedTexImage2D");
#endif
  return 0;
}
