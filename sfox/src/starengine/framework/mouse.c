#include <SDL.h>

#include "mouse.h"

static Uint8 button_state;

void
mouse_update()
{
   button_state = SDL_GetMouseState(NULL, NULL);
}

int
mouse_button_is_down(int num)
{
  return button_state&SDL_BUTTON(num);
}
