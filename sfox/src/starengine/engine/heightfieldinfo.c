#ifdef _WIN32
#include <windows.h>
#endif /*_WIN32*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "stargl.h"

#include "heightfieldinfo.h"

#include "frustum.h"
#include "display.h"
#include "object2d.h"
#include "camera.h"
#include "matrix.h"
#include "vertex.h"
#include "object_factory.h"
#include "texture.h"

#define CELLSIZE 1.0/16.0

struct heightfieldinfo {
  object2d obj;

  heightfield hf;
  camera cam;
};

heightfieldinfo
heightfieldinfo_create(char *landmap, heightfield hf, camera cam, display disp, double sizex, double sizey)
{ 
  matrix4 world;
  heightfieldinfo hfi = malloc(sizeof(struct heightfieldinfo));
    

  matrix4_to_translate(world, display_width(disp)-sizex,
		       display_height(disp)-sizey, 0);
  object2d_init(SF_OBJECT2D(hfi), sizex, sizey, world, material_create_single_texture_from_file(landmap));
  hfi->cam = cam;
  hfi->hf = hf;

  return hfi;
}

/*In 2D mode, y-axis goes downward while in 3D mode it goes upward*/
/* so we have to negate y before drawing the pos in 2D*/
void
heightfieldinfo_to_opengl(heightfieldinfo hfi)
{
  double cellx, celly;
  vector3 pos;
  matrix4 inv;
  camera cam = hfi->cam;

  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  object2d_to_opengl(SF_OBJECT2D(hfi));

  /*Now 0,0 is the center of the minimap*/
  glLoadMatrixd((double *)SF_OBJECT2D(hfi)->world);
  glScalef(SF_OBJECT2D(hfi)->width, SF_OBJECT2D(hfi)->height, 1);
  glTranslatef(0.5, 0.5, 0);

  /*cam space -> heightfield space*/
  matrix4_mul(inv, *heightfield_get_local_matrix(hfi->hf), *heightfield_get_world_matrix(hfi->hf));
  matrix4_to_inverse(inv);
  vector3_mul_matrix4(&pos, &cam->pos, inv);

  cellx = ((int)((pos.x+0.5)*256)/16)/16.0-0.5;
  celly = ((int)((pos.y+0.5)*256)/16)/16.0-0.5;

  /*  fprintf(stderr, "%f %f %f %f\n", pos.x, pos.y, cellx, celly);*/
  /*  fprintf(stderr, "%d %d\n", (int)((pos.x+0.5)*256)/16, (int)((pos.y+0.5)*256)/16);*/

  glDisable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(1,0,0);
  glVertex2f(cellx, -celly-CELLSIZE);
  glVertex2f(cellx+CELLSIZE, -celly-CELLSIZE);
  glVertex2f(cellx+CELLSIZE, -celly);
  glVertex2f(cellx, -celly);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(0,1,0);
  glVertex2f(pos.x-0.01, -pos.y-0.01);
  glVertex2f(pos.x+0.01, -pos.y-0.01);
  glVertex2f(pos.x+0.01, -pos.y+0.01);
  glVertex2f(pos.x-0.01, -pos.y+0.01);
  glEnd();

  /*  fprintf(stderr, "hfi %f\n", -vector3_dot(&cam->pos, &cam->ftm.left.normal));
  vector3_print(&cam->pos);
  vector3_print(&cam->ftm.left.normal);*/
  //  camera_update_frustum(cam);

  glPopAttrib();
}

void
heightfieldinfo_destroy(heightfieldinfo hfi)
{
  object2d_destroy(SF_OBJECT2D(hfi));
  free(hfi);
}
