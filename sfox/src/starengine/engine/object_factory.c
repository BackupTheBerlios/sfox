#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "object3d.h"
#include "vertexbuffer.h"
#include "object_factory.h"

static object3d create_cube(double size);

object3d
object_factory_create(ObjType type, double size)
{
  object3d obj;

  switch(type) {
      case CUBE:
	obj = create_cube(size);
	break;
      default:
	return NULL;
  };
  
  return obj;
}

object3d
create_plan_xy(double sizex, double sizey, int subdiv_x, int subdiv_y)
{
  vertexbuffer vb;

  assert(subdiv_x>0&&subdiv_y>0);

  vb = vertexbuffer_create(VB_STATIC_DRAW, TRIANGLES_INDEXED, (subdiv_x+1)*(subdiv_y+1), subdiv_x*subdiv_y*6);

  vertexbuffer_lock(vb);
  {
    double x, y, stepx, stepy, stepu, stepv, u, v;
    int i, j, k, ofs = 0;
    vertex *vertices = vertexbuffer_get_vertices(vb);
    int *indices = vertexbuffer_get_indices(vb);
  
    x = -1.0*sizex/2;		/* Start at the top-left corner */
    y = 1.0*sizey/2;

    stepx = sizex/(double)subdiv_x;
    stepy = sizey/(double)subdiv_y;

    stepu = 1.0/(double)subdiv_x;
    stepv = 1.0/(double)subdiv_y;

    for(v = 0, j = 0; j < subdiv_y+1; j++) {
      for(u = 0, i = 0; i < subdiv_x+1; i++) {
	vertex_set_coord(&vertices[ofs], x, y, 0);
	vertex_set_tcoord(&vertices[ofs++], 0, u, v);
	x += stepx;
	u += stepu;
      }
      y -= stepy;
      x = -1.0*sizex/2.0;
      v += stepv;
    }
    
    for(i = 0, ofs = 0, j = 0; j < subdiv_y; j++) {
       for(k = 0; k < subdiv_x; k++) {
	indices[ofs] = i+k;
	indices[ofs+1] = i+k+subdiv_x+1;
	indices[ofs+2] = i+k+subdiv_x+2;
   
	indices[ofs+3] = i+k+subdiv_x+2;
	indices[ofs+4] = i+k+1;
	indices[ofs+5] = i+k;
	ofs += 6;	
       }
       i+=k+1;
    }
  }
  vertexbuffer_unlock(vb);

  return object3d_create(matrix4_identity, matrix4_identity, vb, NULL);
}

static object3d
create_cube(double size)
{
  vertex *vertices;
  int *indices;
  vertexbuffer vb;

  vb = vertexbuffer_create(VB_SYSTEM, TRIANGLES_INDEXED, 8, 36);

  vertexbuffer_lock(vb);
  vertices = vertexbuffer_get_vertices(vb);
  indices = vertexbuffer_get_indices(vb);

  vertex_set_coord(&vertices[0], -size, size, size);
  vertex_set_coord(&vertices[1], -size, -size, size);
  vertex_set_coord(&vertices[2], size, -size, size);
  vertex_set_coord(&vertices[3], size, size, size);

  vertex_set_coord(&vertices[4], -size, size, -size);
  vertex_set_coord(&vertices[5], -size, -size, -size);
  vertex_set_coord(&vertices[6], size, -size, -size);
  vertex_set_coord(&vertices[7], size, size, -size);

  vertex_set_color(&vertices[0], 1, 0, 0, 0);
  vertex_set_color(&vertices[1], 1, 0, 0, 0);
  vertex_set_color(&vertices[2], 1, 0, 0, 0);
  vertex_set_color(&vertices[3], 1, 0, 0, 0);
  vertex_set_color(&vertices[4], 1, 0, 0, 0);
  vertex_set_color(&vertices[5], 1, 0, 0, 0);
  vertex_set_color(&vertices[6], 1, 0, 0, 0);
  vertex_set_color(&vertices[7], 1, 0, 0, 0);

  vertex_set_tcoord(&vertices[0], 0, 0, 0);
  vertex_set_tcoord(&vertices[1], 0, 0, 1);
  vertex_set_tcoord(&vertices[2], 0, 1, 1);
  vertex_set_tcoord(&vertices[3], 0, 1, 0);

  vertex_set_tcoord(&vertices[4], 0, 1, 1);
  vertex_set_tcoord(&vertices[5], 0, 1, 0);
  vertex_set_tcoord(&vertices[6], 0, 0, 0);
  vertex_set_tcoord(&vertices[7], 0, 0, 1);

  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;

  indices[3] = 0;
  indices[4] = 2;
  indices[5] = 3;

  indices[6] = 0;
  indices[7] = 5;
  indices[8] = 1;

  indices[9] = 5;
  indices[10] = 0;
  indices[11] = 4;

  indices[12] = 4;
  indices[13] = 7;
  indices[14] = 6;

  indices[15] = 4;
  indices[16] = 6;
  indices[17] = 5;

  indices[18] = 3;
  indices[19] = 2;
  indices[20] = 6;

  indices[21] = 3;
  indices[22] = 6;
  indices[23] = 7;

  indices[24] = 1;
  indices[25] = 5;
  indices[26] = 2;

  indices[27] = 2;
  indices[28] = 5;
  indices[29] = 6;

  indices[30] = 0;
  indices[31] = 3;
  indices[32] = 4;

  indices[33] = 4;
  indices[34] = 3;
  indices[35] = 7;

  vertexbuffer_unlock(vb);

  return object3d_create(matrix4_identity, matrix4_identity, vb, NULL);
}
