#ifdef _WIN32
# include <windows.h>
# include <GL/gl.h>
# include "starglext.h"
#endif /*_WIN32*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "starengine.h"
#include "stargl.h"

#include "vertexbuffer.h"
#include "utility.h"

struct vertexbuffer {
  vertex *vertices;
  int *indices;
  unsigned int num_indices;
  unsigned int num_vertices;
  vertexbuffer_type vbtype;
  vertices_type vtype;
  int lock;

  /*indices for *vertices and *indices */
  /*Allow to use vertexbuffer like a glList*/
  /*They are set to 0 by vertexbuffer_lock*/
  unsigned int vert_i, indi_i;

  /* VBO's ids */
  unsigned int buffer_vertex_id;
  unsigned int buffer_index_id;

  /* glList */
  unsigned int list_id;
};

/**********************************************************************/
/* Macros                                                             */
/**********************************************************************/

/*Conversion macros for VBO(from vertex_buffer_object.txt)*/
#define OFFSET(x) ((char *)NULL + (x))
#define POINTER(x) ((char *)(x) - (char *)NULL)

/*Add offset i to pointer p*/
#define ADDPOINTER(p, i) (OFFSET(((unsigned int)(p))+(i)))

/**********************************************************************/
/* Engine to OpenGL constant conversion                               */
/**********************************************************************/

static const GLuint vb_type[] = { 0, GL_STATIC_DRAW_ARB, GL_DYNAMIC_DRAW_ARB, 0 };
static const GLuint v_type[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP };

/**********************************************************************/
/* Static function definition                                         */
/**********************************************************************/

static vertexbuffer create_vbo(vertexbuffer vb);
static void free_vbo(vertexbuffer vb);
inline static void set_vertex_array_pointers(vertexbuffer vb);

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

vertexbuffer
vertexbuffer_create(vertexbuffer_type vbtype, vertices_type vtype, int num_vertices, int num_indices)
{
  /*indices and vertices *must* be set to 0*/
  vertexbuffer vb = calloc(1, sizeof(struct vertexbuffer));

  vb->num_indices = num_indices;
  vb->num_vertices = num_vertices;
  vb->vbtype = vbtype;
  vb->vtype = vtype;

  switch(vbtype) {
      case VB_SYSTEM:
	vb->vertices = malloc(sizeof(struct vertex)*num_vertices);
	vb->indices = (num_indices>0)?malloc(sizeof(int)*num_indices):NULL;
	break;
      case VB_STATIC_DRAW:
      case VB_DYNAMIC_DRAW:
	vb = create_vbo(vb);
	break;
      case VB_LIST:
	vb->list_id = glGenLists(1);
	break;
      default:
	fprintf(stderr, "!!Vertex Buffer Type unsupported\n");
	free(vb);
	return NULL;
  }

  return vb;
}

void
vertexbuffer_destroy(vertexbuffer vb)
{
  assert(vb);
  switch(vb->vbtype) {
      case VB_STATIC_DRAW:
      case VB_DYNAMIC_DRAW:
	free_vbo(vb);
	break;
      case VB_SYSTEM:
	free(vb->vertices);
	free(vb->indices);
	break;
      case VB_LIST:
	glDeleteLists(vb->list_id, 1);
	break;
  }
  vb->indices = NULL;
  vb->vertices = NULL;
  free(vb);
}

void
vertexbuffer_lock(vertexbuffer vb)
{
  assert(vb->lock==0);
  vb->lock = 1;
  vb->vert_i = vb->indi_i = 0;

  vertexbuffer_bind(vb);

  switch(vb->vbtype) {
      case VB_SYSTEM:
	return;
      case VB_LIST: 
	glNewList(vb->list_id, GL_COMPILE);
	return;
      case VB_DYNAMIC_DRAW:
      case VB_STATIC_DRAW:
	switch(vb->vtype) {
	    case TRIANGLES_INDEXED:
	      vb->indices = glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	    case TRIANGLES_STRIP:
	      vb->vertices = glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	      break;
	    default:
	      break;
	}
  }
}

/*indices and vertices must be set to 0*/
void
vertexbuffer_unlock(vertexbuffer vb)
{
  assert(vb->lock!=0);
  vb->lock=0;

  vertexbuffer_bind(vb);

  switch(vb->vbtype) {
      case VB_SYSTEM:
	break;
      case VB_LIST:
	glEndList();
	break;
      case VB_STATIC_DRAW:
      case VB_DYNAMIC_DRAW:
	switch(vb->vtype) {
	    case TRIANGLES_INDEXED:
	      glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);
	    case TRIANGLES_STRIP:
	      glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
	      vb->vertices = NULL;
	      vb->indices = NULL;
	      break;
	    default:
	      break;
	}
  }
}

vertex *
vertexbuffer_get_vertices(vertexbuffer vb)
{
  assert(vb->lock&&vb->vbtype != VB_LIST);
  return vb->vertices;
}

int *
vertexbuffer_get_indices(vertexbuffer vb)
{
  assert(vb->lock&&vb->vbtype != VB_LIST);
  return vb->indices;
}

unsigned int
vertexbuffer_get_num_indices(vertexbuffer vb)
{
  assert(vb->vbtype != VB_LIST);
  return vb->num_indices;
}

unsigned int
vertexbuffer_get_num_vertices(vertexbuffer vb)
{
  assert(vb->vbtype != VB_LIST);
  return vb->num_vertices;
}

void
vertexbuffer_to_opengl(vertexbuffer vb)
{
  if(vb->vbtype == VB_LIST)
    glCallList(vb->list_id);
  else {
    vertexbuffer_bind(vb);
    set_vertex_array_pointers(vb);

    if(vb->vtype == TRIANGLES_INDEXED) {
      glEnableClientState(GL_INDEX_ARRAY);
      glDrawElements(v_type[vb->vtype], vb->num_indices, GL_UNSIGNED_INT, vb->indices);
    } else
      glDrawArrays(v_type[vb->vtype], 0, vb->num_vertices);
  
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_EDGE_FLAG_ARRAY);
  }
}

void
vertexbuffer_bind(vertexbuffer vb)
{
  if(vb->vbtype != VB_LIST) {
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->buffer_vertex_id);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vb->buffer_index_id);
  }
}

void
vertexbuffer_Begin(vertexbuffer vb, unsigned int type)
{
  if(vb->vbtype == VB_LIST)
    glBegin(type);
}

void
vertexbuffer_End(vertexbuffer vb)
{
  if(vb->vbtype == VB_LIST)
    glEnd();
}

void
vertexbuffer_Vertex3f(vertexbuffer vb, float x, float y, float z)
{
  if(vb->vbtype == VB_LIST)
    glVertex3f(x, y, z);
  else {
    vertex tmp;
    vertex_set_coord(&tmp, x, y, z);
    memcpy(vb->vertices+vb->vert_i, &tmp.coord, sizeof(tmp.coord));
    vb->vert_i += sizeof(tmp);
  }
}

void
vertexbuffer_TexCoord2f(vertexbuffer vb, float u, float v)
{
  if(vb->vbtype == VB_LIST)
    glTexCoord2f(u, v);
  else
    vertexbuffer_MultiTexCoord2f(vb, 0, u, v);
}

void
vertexbuffer_MultiTexCoord2f(vertexbuffer vb, int texunit, float u, float v)
{
  if(vb->vbtype == VB_LIST)
    glMultiTexCoord2f(GL_TEXTURE0+texunit, u, v);
  else {
    vertex tmp;
    vertex_set_tcoord(&tmp, texunit, u, v);
    memcpy(vb->vertices+vb->vert_i+VERTEXOFFSETTCOORD(texunit), &tmp.tcoord, sizeof(tmp.tcoord[texunit]));
  }
}

/****************************************************************************/
/* Local functions                                                          */
/****************************************************************************/

inline static void
set_vertex_array_pointers(vertexbuffer vb)
{
  unsigned int i;

  glColorPointer(4, GL_FLOAT, sizeof(struct vertex), ADDPOINTER(vb->vertices, VERTEXOFFSETCOLOR));

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(struct vertex), vb->vertices);

  for(i = 0; i < MAX_TEXTURES; i++) {
    glActiveTexture(GL_TEXTURE0+i);
    glClientActiveTexture(GL_TEXTURE0+i);
    glTexCoordPointer(2, GL_FLOAT, sizeof(struct vertex), ADDPOINTER(vb->vertices, VERTEXOFFSETTCOORD(i)));
  }
}

static vertexbuffer
create_vbo(vertexbuffer vb)
{
  /* Allocate an index buffer and a vertex buffer for TRIANGLES_INDEXED */
  switch(vb->vtype) {
      case TRIANGLES_INDEXED:
	glGenBuffersARB(1, &vb->buffer_index_id);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vb->buffer_index_id);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(int)*vb->num_indices, NULL, vb_type[vb->vbtype]);
      case TRIANGLES_STRIP:
	glGenBuffersARB(1, &vb->buffer_vertex_id);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->buffer_vertex_id);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(struct vertex)*vb->num_vertices, NULL, vb_type[vb->vbtype]);
	break;
      default:
	fprintf(stderr, "!!Vertex Buffer-Vertex Type combinaison not supported\n");
	free(vb);
	vb = NULL;
	break;
  }
   
  return vb;
}

static void
free_vbo(vertexbuffer vb)
{
  assert(!vb->lock);

  /* We don't want to free usued vbo */
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

  switch(vb->vtype) {
      case TRIANGLES_INDEXED:
	glDeleteBuffersARB(1, &vb->buffer_index_id);
      case TRIANGLES_STRIP:
	glDeleteBuffersARB(1, &vb->buffer_vertex_id);
	break;
  }
}
