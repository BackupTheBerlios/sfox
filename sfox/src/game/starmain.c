#ifdef _WIN32
# include <windows.h>
# include <GL/gl.h>
# undef near
# undef far
#endif /*_WIN32*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "stargl.h"

#include "mathengine.h"
#include "engine.h"
#include "framework.h"
#include "display.h"
#include "utility.h"
#include "fontgl.h"

#define SPEEDCONST 54

#define ZFAR 3000
#define ZNEAR 2

#define CENTERX 400
#define CENTERY 300

double speed_factor = 1;

double camvel = 5;

display screen;

camera camfps;

fontgl font;

int cull_on = 1;
int fill_on = 1;

scene scn;

void draw_frame(unsigned int delta_time);
void handle_keyup(unsigned int key, unsigned int modstat);
void handle_keydown(unsigned int key, unsigned int modstat);
void handle_mouse(SDL_MouseMotionEvent *motion);
void do_move();
void handle_resize(int w, int h);
void print_info();

void
draw_frame(unsigned int delta_time)
{
  glClearColor(0, 0, 1, 0);
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  scene_to_opengl(scn);
  
  if(framework_get_fps() > 1)
    speed_factor = SPEEDCONST/framework_get_fps();

  print_info();

  do_move();
}

void
print_info()
{
  fontgl_printf(font, 0, 0, 0, "%.2f FPS",  framework_get_fps());
  fontgl_printf(font, 0, 20, 0, "cam <pos> x:%.2f y:%.2f z:%.2f", camfps->pos.x, camfps->pos.y,camfps->pos.z);
  fontgl_printf(font, 0, 80, 0, "Speed factor: %.2f", speed_factor);

  /* Frutum tests */
/*   { */
/*     frustum2d ftm2d; */
/*     bbox2d bb; */

/*     bbox2d_set(&bb, -500, 500, 500, -500); */
/*     frustum_to_frustum2d(&ftm2d, &camfps->ftm); */

/*     if(frustum2d_bbox_is_into(&ftm2d, &bb)) */
/*       fontgl_printf(font, 0, 100, 0, "You are in the map."); */
/*     else */
/*       fontgl_printf(font, 0, 100, 0, "You are'nt in the map."); */

/*     if(frustum_point_is_into(&camfps->ftm, 0, 0, 0)) */
/*       fontgl_printf(font, 0, 60, 0, "You see (0,0)"); */
/*     else */
/*       fontgl_printf(font, 0, 60, 0, "You don't see (0,0)"); */
/*   } */

}

/****************************************************************************/
/* Input functions                                                          */
/****************************************************************************/

void
do_move()
{
  if(keyboard_is_down(SDLK_UP))
    camera_move_along_view(camfps, camvel*speed_factor);
  else if(keyboard_is_down(SDLK_DOWN))
    camera_move_along_view(camfps, -camvel*speed_factor);
  if(keyboard_is_down(SDLK_LEFT))
    camera_side_move(camfps, -camvel*speed_factor);
  else if(keyboard_is_down(SDLK_RIGHT))
    camera_side_move(camfps, camvel*speed_factor);

  if(mouse_button_is_down(1))
    printf("Button 1\n");
}

void
handle_keyup(unsigned int key, unsigned int modstat)
{
  switch(key) {
      default:
	/*printf("Key %d up\n", key);*/
	break;
  }
}

void
handle_keydown(unsigned int key, unsigned int modstat)
{
  switch(key) {
      case SDLK_ESCAPE:
      case SDLK_q:
	SDL_WM_GrabInput(SDL_GRAB_OFF);
	framework_exit(EXIT_SUCCESS);
	break;
      case SDLK_f:
	if(fill_on)
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	fill_on = !fill_on;
	break;
      case SDLK_c:
	if(cull_on)
	  glDisable(GL_CULL_FACE);
	else
	  glEnable(GL_CULL_FACE);
	cull_on = !cull_on;
	break;
  default:
	break;
  }
}

/*It's a handler, it doesn't depend of the FPS*/
void
handle_mouse(SDL_MouseMotionEvent *motion)
{
  static double rx = 0;
  static double ry = 0;

  if(motion->x == CENTERX && motion->y == CENTERY) 
    return;  

  //camera_mouse_move(camfps, (double)motion->xrel/400.0, (double)motion->yrel/400.0);
  rx = (double)motion->xrel/10.0;
  ry = (double)motion->yrel/10.0;

  camera_mouse_move(camfps, rx, ry);
}

/*****************************************************************************/
void
handle_resize(int w, int h)
{
  printf("Resize %d %d\n", w, h);
}

/*****************************************************************************/
/* Init                                                                      */
/*****************************************************************************/

void init()
{
  heightfield hf;
  heightfieldinfo hfi;
  skybox sb;
  object3d *plan = create_plan_xy(100, 100, 1, 1);
  material mat = material_create(NULL, 0, &color_red, 0, 0);
  vector3 cam_pos = {0,0,0};
  vector3 cam_up = {0,1,0};
  viewport vp = viewport_create(0, 0, display_width(screen), display_height(screen));

  /* Camera */
  camfps = camera_create(60, ZFAR, ZNEAR, &cam_pos, &cam_up, vp);

  /* Heightfied creation */
  hf = heightfield_create_from_file(camfps, "data/height.png", 1000, 1000, 100);
  heightfield_set_textures_from_file(hf, "data/land.jpg", "data/detail.jpg");
  heightfield_set_detail_scale(hf, 50, 50);
  //matrix4_to_rot_x(tmp, 90);
  //heightfield_set_world_matrix(hf, tmp);

  /* Heightfield infos*/
  hfi = heightfieldinfo_create("data/land.jpg", hf, camfps, screen, 250, 250);

  /* Skybox */
   sb = skybox_create(camfps, "data/left.jpg", "data/right.jpg", "data/front.jpg", "data/back.jpg", "data/top.jpg", "data/bottom.jpg", 10);

  /* Test plane */
  object3d_set_material(plan, mat);

  /* Populate the scene */
  scn = scene_create();
  scene_set_camera(scn, camfps);
  scene_set_display(scn, screen);
  scene_add_object(scn, sb, (void *)skybox_to_opengl, NULL);
  scene_add_object(scn, hf, (void *)heightfield_to_opengl, NULL);
  scene_add_object(scn, plan, (void *)object3d_to_opengl, NULL);
  scene_add_object2d(scn, hfi, (void *)heightfieldinfo_to_opengl, NULL);

  fontgl_init();
  font = fontgl_create("data/vera.ttf", 800, 600, 16);
  fontgl_set_color(font, 1,0,0);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  SDL_WarpMouse(CENTERX,CENTERY);
  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);
}

/*****************************************************************************/
/* App start                                                                 */
/*****************************************************************************/
void
app_init(int argc, char **argv)
{
  framework_set_mouse_handler(handle_mouse);
  framework_set_keyboard_handlers(handle_keyup, handle_keydown);
  framework_set_frame_handler(draw_frame);
  framework_set_resize_handler(handle_resize);
  
  screen = display_create("Star", 800, 600, 24, 0);
  starengine_init();
  init();
}
