#include "Draw.h"
#include <vector>
#include <SDL_ttf.h>

void drawPoints(SDL_Renderer *renderer, std::vector<Vector2> points, Vector2 position, int angle) {
    for (int i = 0; i < points.size(); i++) {
        Vector2 point = points[i];
        Vector2 nextPoint = points[(i + 1) % points.size()];
        
        point.rotate(angle);
        nextPoint.rotate(angle);
        
        SDL_RenderDrawLine(renderer, position.x + point.x, position.y + point.y, position.x + nextPoint.x, position.y + nextPoint.y);
    }
}

void drawText(SDL_Renderer *renderer, TTF_Font* font, const char* text, Vector2 pos, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {static_cast<int>(pos.x), static_cast<int>(pos.y), surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

