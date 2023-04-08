#include "Draw.h"

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (surface == nullptr) {
        printf("Failed to load image: %s", IMG_GetError());
        exit(-1);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void drawTexture(SDL_Renderer *renderer ,SDL_Texture *texture, int x, int y, int angle) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}
