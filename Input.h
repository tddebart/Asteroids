#ifndef SHOOT_UP_2D_INPUT_H
#define SHOOT_UP_2D_INPUT_H

#include <SDL.h>

static bool isKeyPressed(SDL_Scancode key) {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    return state[key];
}

#endif //SHOOT_UP_2D_INPUT_H
