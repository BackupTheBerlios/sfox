#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stargl.h"

#include "vertexbuffer.h"

struct vertexbuffer {
  vertex *vertices;
  int *indices;
  unsigned int num_indices;
  unsigned int num_vertices;
  vertexbuffer_type type;
  int lock;
};

vertexbuffer
vertexbuffer_create(vertexbuffer_type type, int num_vertices, int num_indices)
{
  vertexbuffer vb = malloc(sizeof(struct vertexbuffer));
  
  vb->vertices = malloc(sizeof(struct vertex)*num_vertices);
  vb->lock = 0;

  if(num_indices>0)
    vb->indices = malloc(sizeof(int)*num_indices);
  else
    vb->indices = NULL;

  vb->num_indices = num_indices;
  vb->num_vertices = num_vertices;
  vb->type = type;

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
  vb->lock++;
}

void
vertexbuffer_unlock(vertexbuffer vb)
{
  assert(vb->lock!=0);
  vb->lock--;
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

  glColorPointer(4, GL_DOUBLE, sizeof(struct vertex), &(vb->vertices->col));

  for(i = 0; i < MAX_TEXTURES; i++) {
    glActiveTexture(GL_TEXTURE0+i);
    glClientActiveTexture(GL_TEXTURE0+i);
    glTexCoordPointer(2, GL_DOUBLE, sizeof(struct vertex), &(vb->vertices->tcoord[0]));
  }

  if(vb->type == TRIANGLES_INDEXED) {
    gltype = GL_TRIANGLES;
    num_elem_to_draw = vb->num_indices;
  } else
    glDisableClientState(GL_INDEX_ARRAY);

  if(vb->type == TRIANGLES_STRIP) {
    gltype = GL_TRIANGLE_STRIP;
    num_elem_to_draw = vb->num_vertices;
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, sizeof(struct vertex), &vb->vertices->coord);

  if(vb->type == TRIANGLES_INDEXED) {
    assert(vb->indices);
    glDrawElements(gltype, num_elem_to_draw, GL_UNSIGNED_INT, vb->indices);
  } else
    glDrawArrays(gltype, 0, num_elem_to_draw);

  glActiveTexture(GL_TEXTURE0);
  glClientActiveTexture(GL_TEXTURE0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_INDEX_ARRAY);
  glDisableClientState(GL_EDGE_FLAG_ARRAY);
}
