#ifndef SHOOT_UP_2D_DRAW_H
#define SHOOT_UP_2D_DRAW_H

#include <SDL_render.h>
#include <SDL_image.h>

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *filename);

void drawTexture(SDL_Renderer *renderer ,SDL_Texture *texture, int x, int y, int angle = 0);

#endif //SHOOT_UP_2D_DRAW_H
