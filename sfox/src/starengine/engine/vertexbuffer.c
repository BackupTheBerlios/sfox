#ifdef _WIN32
#include <windows.h>
#endif /*_WIN32*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stargl.h"
#include "starglu.h"

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

  unsigned int buffer_vertex_id;
  unsigned int buffer_index_id;
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

static const GLuint vb_type[] = { 0, GL_STATIC_DRAW_ARB, GL_DYNAMIC_DRAW_ARB };
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
  if(vb->vbtype != VB_SYSTEM)
    free_vbo(vb);
  else {
    free(vb->vertices);
    free(vb->indices);
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

  vertexbuffer_bind(vb);

  if(vb->vbtype == VB_SYSTEM)
    return;

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

/*indices and vertices must be set to 0*/
void
vertexbuffer_unlock(vertexbuffer vb)
{
  assert(vb->lock!=0);
  vb->lock=0;

  vertexbuffer_bind(vb);

  if(vb->vbtype == VB_SYSTEM)
    return;

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

vertex *
vertexbuffer_get_vertices(vertexbuffer vb)
{
  assert(vb->lock);
  return vb->vertices;
}

int *
vertexbuffer_get_indices(vertexbuffer vb)
{
  assert(vb->lock);
  return vb->indices;
}

unsigned int
vertexbuffer_get_num_indices(vertexbuffer vb)
{
  return vb->num_indices;
}

unsigned int
vertexbuffer_get_num_vertices(vertexbuffer vb)
{
  return vb->num_vertices;
}

void
vertexbuffer_to_opengl(vertexbuffer vb)
{
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

void
vertexbuffer_bind(vertexbuffer vb)
{
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->buffer_vertex_id);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vb->buffer_index_id);
}

/****************************************************************************/
/* Local functions                                                          */
/****************************************************************************/

inline static void
set_vertex_array_pointers(vertexbuffer vb)
{
  unsigned int i;

  glColorPointer(4, GL_DOUBLE, sizeof(struct vertex), ADDPOINTER(vb->vertices, VERTEXOFFSETCOLOR));

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, sizeof(struct vertex), vb->vertices);

  for(i = 0; i < MAX_TEXTURES; i++) {
    glActiveTexture(GL_TEXTURE0+i);
    glClientActiveTexture(GL_TEXTURE0+i);
    glTexCoordPointer(2, GL_DOUBLE, sizeof(struct vertex), ADDPOINTER(vb->vertices, VERTEXOFFSETTCOORD(i)));
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
