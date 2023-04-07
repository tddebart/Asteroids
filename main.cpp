﻿#define SDL_MAIN_HANDLED

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "draw.cpp"
#include <windows.h>
#include "Entity.cpp"

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;

vector<Entity> entities;

bool done = false;

void initSDL();
void doInput();

int main() {
    initSDL();

    auto shuttle = loadTexture(renderer,"assets/shuttle.png");
    
    // Add entities
    auto player = Entity(shuttle);
    player.position.x = 100;
    player.position.y = 100;
    entities.push_back(player);


    while (!done) {
        doInput();

        SDL_SetRenderDrawColor(renderer, 96, 128,255,255);
        SDL_RenderClear(renderer);

        for (auto entity: entities) {
            drawTexture(renderer, entity.texture, entity.position.x, entity.position.y);
        }
        
        SDL_RenderPresent(renderer);
        

    }
    
    return 0;
}

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to start SDL: %s", SDL_GetError());
        exit(-1);
    }
    
    SetProcessDPIAware();

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
//    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "1");
//    SDL_SetHint(SDL_HINT_WINDOWS_DPI_SCALING, "1");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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