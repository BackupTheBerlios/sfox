#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>

#include "keyboard.h"
#include "mouse.h"

typedef void (*resize_func) (int, int);
typedef void (*draw_func) (unsigned int delta_time);
typedef void (*mouse_func) (SDL_MouseMotionEvent *motion);

/* Input handlers setters */
extern void framework_set_mouse_handler(mouse_func mouse_handler);
extern void framework_set_keyboard_handlers(keyb_func keyboard_up, keyb_func keyboard_down);
extern void framework_set_keyup_handler(keyb_func keyboard_handler);
extern void framework_set_keydown_handler(keyb_func keyboard_handler);

extern void framework_set_resize_handler(resize_func resize_handler);

/* Draw function setter */
extern void framework_set_frame_handler(draw_func frame_handler);

/* When you want to quit */
extern void framework_exit(int ret);

/*User application's entry point*/
extern void app_init(int argc, char **argv);

/* Time needed in ms for drawing last frame */
extern unsigned int framework_get_delta();

/* Frame per sec */
extern float framework_get_fps();

#endif
