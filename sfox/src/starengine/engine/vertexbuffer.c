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

  unsigned int buffer_id;

};

/**********************************************************************/
/* Engine to OpenGL constant conversion                               */
/**********************************************************************/

static const GLuint vb_type[] = { 0, GL_STATIC_DRAW_ARB, GL_DYNAMIC_DRAW_ARB };
static const GLuint v_type[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP };

/**********************************************************************/
/* Static function definition                                         */
/**********************************************************************/

static vertexbuffer create_vbo(vertexbuffer vb);
static void vbo_to_opengl(vertexbuffer vb);

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

vertexbuffer
vertexbuffer_create(vertexbuffer_type vbtype, vertices_type vtype, int num_vertices, int num_indices)
{
  vertexbuffer vb = malloc(sizeof(struct vertexbuffer));

  vb->num_indices = num_indices;
  vb->num_vertices = num_vertices;
  vb->vbtype = vbtype;
  vb->vtype = vtype;
  vb->lock = 0;
  vb->vertices = NULL;
  vb->indices = NULL;
  
  switch(vbtype) {
      case VB_SYSTEM:
	vb->vertices = malloc(sizeof(struct vertex)*num_vertices);
	vb->indices = (num_indices>0)?malloc(sizeof(int)*num_indices):NULL;
	break;
      case VB_STATIC_DRAW:
      case VB_DYNAMIC_DRAW:
	return create_vbo(vb);
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
  free(vb->vertices);
  free(vb->indices);
  vb->indices = NULL;
  vb->vertices = NULL;
  free(vb);
}

void
vertexbuffer_lock(vertexbuffer vb)
{
  assert(vb->lock==0);
  vb->lock = 1;
  if(vb->vbtype != VB_SYSTEM) {
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->buffer_id);
    vb->vertices = glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
  }    
}

void
vertexbuffer_unlock(vertexbuffer vb)
{
  assert(vb->lock!=0);
  if(vb->vbtype != VB_SYSTEM) {
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->buffer_id);
    glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  }
  vb->lock=0;
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
  int i;
  int gltype, num_elem_to_draw;

  if(vb->vbtype != VB_SYSTEM ) {
    vbo_to_opengl(vb);
  } else {
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    glColorPointer(4, GL_DOUBLE, sizeof(struct vertex), &(vb->vertices->col));

    for(i = 0; i < MAX_TEXTURES; i++) {
      glActiveTexture(GL_TEXTURE0+i);
      glClientActiveTexture(GL_TEXTURE0+i);
      glTexCoordPointer(2, GL_DOUBLE, sizeof(struct vertex), &(vb->vertices->tcoord[0]));
    }

    if(vb->vtype == TRIANGLES_INDEXED) {
      gltype = GL_TRIANGLES;
      num_elem_to_draw = vb->num_indices;
    } else
      glDisableClientState(GL_INDEX_ARRAY);

    if(vb->vtype == TRIANGLES_STRIP) {
      gltype = GL_TRIANGLE_STRIP;
      num_elem_to_draw = vb->num_vertices;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, sizeof(struct vertex), &vb->vertices->coord);

    if(vb->vtype == TRIANGLES_INDEXED) {
      assert(vb->indices);
      glDrawElements(gltype, num_elem_to_draw, GL_UNSIGNED_INT, vb->indices);
    } else
      glDrawArrays(gltype, 0, num_elem_to_draw);
  }

  glActiveTexture(GL_TEXTURE0);
  glClientActiveTexture(GL_TEXTURE0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_INDEX_ARRAY);
  glDisableClientState(GL_EDGE_FLAG_ARRAY);
}

/****************************************************************************/
/* Local functions                                                          */
/****************************************************************************/

static vertexbuffer
create_vbo(vertexbuffer vb)
{
  unsigned int i;

  glGenBuffersARB(1, &vb->buffer_id);

  switch(vb->vtype) {
      case TRIANGLES_STRIP:
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->buffer_id);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(struct vertex)*vb->num_vertices, NULL, vb_type[vb->vbtype]);
	break;
      default:
	fprintf(stderr, "!!Vertex Buffer-Vertex Type combinaison not supported\n");
	free(vb);
	vb = NULL;
	break;
  }
   
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

  return vb;
}

static void
vbo_to_opengl(vertexbuffer vb)
{
  int i;
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->buffer_id);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, sizeof(struct vertex), 0);
  for(i = 0; i < MAX_TEXTURES; i++) {
    glActiveTexture(GL_TEXTURE0+i);
    glClientActiveTexture(GL_TEXTURE0+i);
    glTexCoordPointer(2, GL_DOUBLE, sizeof(struct vertex), sizeof(vector3)+i*sizeof(vector2));
  }

  glDrawArrays(v_type[vb->vtype], 0, vb->num_vertices);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}
