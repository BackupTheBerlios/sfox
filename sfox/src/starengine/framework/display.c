#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL.h>

#include "display.h"

struct display {
    SDL_Surface *surface;
};

display
display_create(const char *title, int resx, int resy, int bpp, int fullscreen)
{
    display disp;
    int flags = SDL_OPENGL|SDL_RESIZABLE;

    if( fullscreen )
	flags |= SDL_FULLSCREEN;

    disp = malloc(sizeof(struct display));
    disp->surface = SDL_SetVideoMode(resx, resy, bpp, flags);
    if( !disp->surface ) {
	fprintf(stderr, "Erreur d'initialisation du mode video %dx%dx%d: %s\n",
		resx, resy, bpp, SDL_GetError());
	exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption(title, NULL);
    /*SDL_WarpMouse(100,100);*/

    return disp;
}

void
display_destroy(display disp)
{
    assert(disp);
    free(disp);
}

int
display_width (display disp)
{
    return disp->surface->w;
}

int
display_height (display disp)
{
    return disp->surface->h;
}
