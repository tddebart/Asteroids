#ifndef SHOOT_UP_2D_DRAW_H
#define SHOOT_UP_2D_DRAW_H

#include <SDL_render.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include "Vector2.h"

void drawText(SDL_Renderer *renderer,TTF_Font* font, const char* text, Vector2 pos, SDL_Color color);

void drawPoints(SDL_Renderer *renderer, std::vector<Vector2> points, Vector2, int angle = 0);

#endif //SHOOT_UP_2D_DRAW_H
