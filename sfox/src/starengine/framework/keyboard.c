#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <assert.h>

#include "keyboard.h"

static keyb_func keyboard_key_down = NULL;
static keyb_func keyboard_key_up = NULL;
static Uint8 keystate[SDLK_LAST];
static Uint8 *newstate = NULL;

void
keyboard_init(keyb_func key_up, keyb_func key_down)
{
  keyboard_key_up = key_up;
  keyboard_key_down = key_down;
}

void
keyboard_update(void)
{
  unsigned int i;
  unsigned int modstat;

  assert(keyboard_key_down&&keyboard_key_up);
  newstate = SDL_GetKeyState(NULL);
  modstat = SDL_GetModState();

  for(i = SDLK_FIRST; i < SDLK_LAST; i++) {
    if( keystate[i] != newstate[i] ) {
      if( newstate[i] == 1 )
        keyboard_key_down(i, modstat);
      else
        keyboard_key_up(i, modstat);
    }
    keystate[i] = newstate[i];
  }
}

int
keyboard_is_down(unsigned int key)
{
  assert(key<SDLK_LAST);
  return newstate[key]!=0;
}
