#ifdef _WIN32
# include <windows.h>
#endif /*_WIN32*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stargl.h"
#include "starutils.h"

#include "scene.h"
#include "camera.h"


struct rendering_elem {
  renderfunc to_opengl_func;
  void *object;
  void *data;
};

struct scene {
  camera cam;
  display disp;			/* Needed for 2d rendering */
  SSList *render_list;
  SSList *render2d_list;
};

/**********************************************************************/
/* Static declarations                                                */
/**********************************************************************/

static void slist_to_opengl(SSList *list);
static struct rendering_elem *create_rendering_elem(void *object, renderfunc func, void *data);
static void scene3d_to_opengl(scene scn);
static void scene2d_to_opengl(scene scn);

/**********************************************************************/
/* And now for something completely different                         */
/**********************************************************************/

scene
scene_create()
{
  scene scn = malloc(sizeof(struct scene));
  scn->render_list = NULL;
  scn->render2d_list = NULL;
  scn->cam = NULL;
  scn->disp = NULL;

  return scn;
}

void
scene_to_opengl(scene scn)
{
  scene3d_to_opengl(scn);
  scene2d_to_opengl(scn);
}

void
scene_add_object(scene scn, void *object, renderfunc func, void *data)
{
  struct rendering_elem *elem = create_rendering_elem(object, func, data);

  scn->render_list = s_slist_append(scn->render_list, elem);
}

void
scene_add_object2d(scene scn, void *object, renderfunc func, void *data)
{
  struct rendering_elem *elem = create_rendering_elem(object, func, data);
  
  scn->render2d_list = s_slist_append(scn->render2d_list, elem);
}


void
scene_set_camera(scene scn, camera cam)
{
  scn->cam = cam;
}

void
scene_set_display(scene scn, display disp)
{
  scn->disp = disp;
}

/***********************************************************************/
/* Static functions                                                    */
/***********************************************************************/

static void
slist_to_opengl(SSList *list)
{
  while(list) {
    struct rendering_elem *rel = (struct rendering_elem *)list->data;
    glPushMatrix();
    rel->to_opengl_func(rel->object);
    glPopMatrix();
    list = s_slist_next(list);
  }
}

static struct rendering_elem *
create_rendering_elem(void *object, renderfunc func, void *data)
{
  struct rendering_elem *elem = malloc(sizeof(struct rendering_elem));
  
  elem->to_opengl_func = func;
  elem->object = object;
  elem->data = data;

  return elem;
}

static void
scene3d_to_opengl(scene scn)
{
  if(scn->cam == NULL)
    return;

  camera_to_opengl(scn->cam);
  slist_to_opengl(scn->render_list);
}

static void
scene2d_to_opengl(scene scn)
{
  if(scn->disp == NULL)
    return;

  glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, display_width(scn->disp), display_height(scn->disp), 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();	/* Not needed, here only for experimenting frustum*/
  glLoadIdentity();

  slist_to_opengl(scn->render2d_list);
  
  glMatrixMode(GL_PROJECTION);
   glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  glPopMatrix();
}
