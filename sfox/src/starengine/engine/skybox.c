#include <stdlib.h>

#include "stargl.h"

#include "skybox.h"

#include "camera.h"
#include "object3d.h"
#include "object_factory.h"

enum {FRONT=0, BOTTOM, LEFT, RIGHT, TOP, BACK, LAST};

/* TODO: Use only one object */
struct skybox {
  camera cam;
  object3d *obj[6];
  double sx;
};

static void create_quad(float size);

skybox
skybox_create(camera cam, char *left, char *right, char *front, char *back, char *top, char *bottom, float sx)
{
  unsigned int i;
  material mat[6];
  texture tex[6];
  skybox sb = (skybox)malloc(sizeof(struct skybox));
  sb->cam = cam;

  tex[FRONT] = texture_create_from_file(front);
  tex[BACK] = texture_create_from_file(back);
  tex[LEFT] = texture_create_from_file(left);
  tex[RIGHT] = texture_create_from_file(right);
  tex[TOP] = texture_create_from_file(top);
  tex[BOTTOM] = texture_create_from_file(bottom);

  sb->sx = sx;

  for(i = 0; i < LAST; i++) {
    texture_add_texture_env(tex[i], GL_TEXTURE_ENV_MODE, GL_REPLACE);
    texture_set_st_clamp_mode(tex[i], CLAMP_TO_EDGE);
    texture_set_min_filter_mode(tex[i], LINEAR);
    texture_set_mag_filter_mode(tex[i], LINEAR);
    mat[i] = material_create(&tex[i], 1, NULL, 0, 0);
    sb->obj[i] = object3d_create(matrix4_identity, NULL, mat[i]);
  }

  object3d_BeginList(sb->obj[FRONT]);
   glPushMatrix();
   glTranslatef(0, 0, -sx/2);
   create_quad(sx);	
   glPopMatrix();
  object3d_EndList();

  object3d_BeginList(sb->obj[BACK]);
   glPushMatrix();
   glTranslatef(0, 0, sx/2);
   glRotatef(180, 0, 1, 0);
   create_quad(sx);	
   glPopMatrix();
  object3d_EndList();

  object3d_BeginList(sb->obj[LEFT]);
   glPushMatrix();
   glTranslatef(-sx/2, 0, 0);
   glRotatef(90, 0, 1, 0);
   create_quad(sx);	
   glPopMatrix();
  object3d_EndList();

  object3d_BeginList(sb->obj[RIGHT]);
   glPushMatrix();
   glTranslatef(sx/2, 0, 0);
   glRotatef(-90, 0, 1, 0);
   create_quad(sx);
   glPopMatrix();
  object3d_EndList();

  object3d_BeginList(sb->obj[TOP]);
   glPushMatrix();
   glTranslatef(0, sx/2, 0);
   glRotatef(90, 1, 0, 0);
   create_quad(sx);
   glPopMatrix();
  object3d_EndList();

  object3d_BeginList(sb->obj[BOTTOM]);
   glPushMatrix();
   glTranslatef(0, -sx/2, 0);
   glRotatef(-90, 1, 0, 0);
   create_quad(sx);
   glPopMatrix();
  object3d_EndList();

  return sb;
}

void
skybox_to_opengl(skybox sb)
{
  int i;
  matrix4 world;
  glDisable(GL_DEPTH_TEST);

  matrix4_to_translate(world, sb->cam->pos.x, sb->cam->pos.y, sb->cam->pos.z);
  for(i = 0; i < LAST; i++)
    object3d_set_world_matrix(sb->obj[i], world);

  object3d_to_opengl(sb->obj[FRONT]);
  object3d_to_opengl(sb->obj[BACK]);
  object3d_to_opengl(sb->obj[LEFT]);
  object3d_to_opengl(sb->obj[RIGHT]);
  object3d_to_opengl(sb->obj[TOP]);
  object3d_to_opengl(sb->obj[BOTTOM]);

  glEnable(GL_DEPTH_TEST);
}

static void
create_quad(float size)
{
  object3d_Begin(GL_QUADS);
   object3d_TexCoord2f(0, 0);
   object3d_Vertex3f(-size/2, size/2, 0);
   object3d_TexCoord2f(0, 1);
   object3d_Vertex3f(-size/2, -size/2, 0);
   object3d_TexCoord2f(1, 1);
   object3d_Vertex3f(size/2, -size/2, 0);
   object3d_TexCoord2f(1, 0);
   object3d_Vertex3f(size/2, size/2, 0);
  object3d_End();
}
