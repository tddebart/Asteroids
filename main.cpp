#define SDL_MAIN_HANDLED

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include <iostream>
#include <SDL.h>

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;

bool done = false;

void doInput();

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to start SDL: %s", SDL_GetError());
        return -1;
    }
    
    window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    while (!done) {
        doInput();

        SDL_SetRenderDrawColor(renderer, 96, 128,255,255);
        SDL_RenderClear(renderer);
        
        SDL_RenderPresent(renderer);
        
//        SDL_Delay(16);
    }
    
    return 0;
}

void doInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                done = true;
                break;

            default:
                break;
        }
    }
}
