#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL.h>

typedef void (*keyb_func) (unsigned int key, unsigned int modstat);

extern void keyboard_init(keyb_func key_up, keyb_func key_down);
extern void keyboard_update(void);
extern inline int keyboard_is_down(unsigned int key);

#endif
