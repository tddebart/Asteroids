#include <SDL_render.h>
#include <SDL_image.h>

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *filename) {
    SDL_Surface *surface = IMG_Load(filename);
    if (surface == nullptr) {
        printf("Failed to load image: %s", IMG_GetError());
        exit(-1);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void drawTexture(SDL_Renderer *renderer ,SDL_Texture *texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}
