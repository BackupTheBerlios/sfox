#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <SDL.h>

#include "framework.h"
#include "keyboard.h"

#define FPS_CALC_INTERVAL 5 /* Calculate fps every n frames */

/* Default framework handlers */
static void default_keydown_handler(unsigned int key, unsigned int modstat);
static void default_keyup_handler(unsigned int key, unsigned int modstat);
static void default_mouse_handler(SDL_MouseMotionEvent *motion);
static void default_frame_handler(unsigned int delta_time);
static void default_resize_handler(int newx, int newy);

static draw_func draw_frame = default_frame_handler;
static keyb_func handle_keyup = default_keyup_handler;
static keyb_func handle_keydown = default_keydown_handler;
static mouse_func handle_mouse = default_mouse_handler;
static resize_func handle_resize = default_resize_handler;

static int framework_running = 1;
static unsigned int delta_time = 0;
static float fps = 0;

/* Internal functions */
static void quit_sdl();
static void msg_loop();

/*****************************************************************************/
/* Default framework handlers                                                */
/*****************************************************************************/
static void
default_resize_handler(int newx, int newy)
{
}

static void
default_keydown_handler(unsigned int key, unsigned int modstat)
{
}

static void
default_keyup_handler(unsigned int key, unsigned int modstat)
{
    if (key == SDLK_ESCAPE)
	framework_exit(EXIT_SUCCESS);
}

static void
default_mouse_handler(SDL_MouseMotionEvent *motion)
{
}

static void
default_frame_handler(unsigned int delta_time)
{
}

/*****************************************************************************/
/* Handler setters                                                           */
/*****************************************************************************/
void
framework_set_resize_handler(resize_func resize_handler)
{
    handle_resize = resize_handler;
}

void
framework_set_mouse_handler(mouse_func mouse_handler)
{
    handle_mouse = mouse_handler;
}

void
framework_set_keyboard_handlers(keyb_func keyboard_up, keyb_func keyboard_down)
{
    handle_keyup = keyboard_up;
    handle_keydown = keyboard_down;
}

void
framework_set_keyup_handler(keyb_func keyboard_handler)
{
    handle_keyup = keyboard_handler;
}

void
framework_set_keydown_handler(keyb_func keyboard_handler)
{
    handle_keydown = keyboard_handler;
}

void
framework_set_frame_handler(draw_func frame_handler)
{
    draw_frame = frame_handler;
}

/*****************************************************************************/
unsigned int
framework_get_delta()
{
    return delta_time;
}

float
framework_get_fps()
{
    return fps;
}

void
framework_exit(int ret)
{
    quit_sdl();
    exit(ret);
}

/*****************************************************************************/
/* Framework internal functions                                              */
/*****************************************************************************/
static void
init_sdl()
{
    if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_NOPARACHUTE) == -1 ) {
	fprintf(stderr, "Erreur d'initialisation de la SDL: %s\n",
		SDL_GetError());
	exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    signal(SIGSEGV, quit_sdl);
    signal(SIGABRT, quit_sdl);
    signal(SIGINT, quit_sdl);
}

static void
quit_sdl()
{
    SDL_WM_GrabInput(SDL_GRAB_OFF);
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Quit();
}

static void
calc_fps()
{
    static unsigned int frame = 0;
    static unsigned int elapsed_time = 0;

    frame++;	
    elapsed_time += delta_time;
    if(frame >= FPS_CALC_INTERVAL) {
	fps = 1000*frame/(float)elapsed_time;
	frame = 0;
	elapsed_time = 0;
    }
}

static void
msg_loop()
{
    unsigned int previous_time;

    SDL_Event event;
    while( framework_running ) {
	SDL_PumpEvents();
	keyboard_update();
	mouse_update();
	while( SDL_PollEvent( &event ) ) {
	    switch( event.type ) {
		case SDL_MOUSEMOTION:
		    handle_mouse(&event.motion);
		    break;
		case SDL_VIDEORESIZE:
		    handle_resize(event.resize.w, event.resize.h);
		    break;
		default:
		    break;
	    }
	}
	previous_time = SDL_GetTicks();
	draw_frame(delta_time);
	SDL_GL_SwapBuffers();	
	delta_time = SDL_GetTicks() - previous_time;
	calc_fps();
    }
}

int
main(int argc, char *argv[])
{
    SDL_Event event;

    init_sdl();
    app_init(argc, argv);

    while(SDL_PollEvent(&event)); /* Removes startup parasite events */

    keyboard_init(handle_keyup, handle_keydown);
    msg_loop();
    assert(0);			/* Never reached */

    return EXIT_FAILURE;
}
