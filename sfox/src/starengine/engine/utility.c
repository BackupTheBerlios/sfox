#ifdef _WIN32
#include <windows.h>
#include "starglaux.h"
#endif /*_WIN32*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stargl.h"
#include "starglu.h"

#include "utility.h"

void
printgl_error(const char *file, int line)
{       
  GLenum errcode;
  if((errcode = glGetError()) != GL_NO_ERROR)
    fprintf(stderr, "***File %s:%d:  %s\n", file, line, gluErrorString(errcode));
}  
