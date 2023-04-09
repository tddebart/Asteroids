#define SDL_MAIN_HANDLED

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>

#include "Draw.h"
#include "Entities/Player.cpp"
#include "Entities/Star.cpp"
#include "Entities/Asteroid.cpp"
#include "ScreenInfo.h"

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;

bool done = false;
void initSDL();
void doInput();

int main() {
    initSDL();
    srand(time(nullptr));
    
    // Add stars
    for (int i = 0; i < 200; i++) {
        Star* star = new Star(nullptr, Vector2(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
        Entity::entities.push_back(star);
    }
    
    // Add entities
    auto player = Player(nullptr, Vector2(100,100));
    Entity::entities.push_back(&player);
    
    for (int i = 0; i < 10; i++) {
        auto* asteroid = new Asteroid(Vector2(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
        Entity::entities.insert(Entity::entities.begin(), asteroid);
    }


    while (!done) {
        doInput();

        SDL_SetRenderDrawColor(renderer, 0, 0,0,255);
        SDL_RenderClear(renderer);

        
        for (auto entity: Entity::entities) {
            entity->update();
            entity->draw(renderer);

            if (entity->remove) {
                Entity::entities.erase(std::remove(Entity::entities.begin(), Entity::entities.end(), entity), Entity::entities.end());
            }
        }
        
        auto asteroids = std::vector<Asteroid*>();
        for (auto entity : Entity::entities) {
            if (entity->type == "Asteroid") {
                asteroids.push_back((Asteroid*)entity);
            }
        }
        for (auto projectile : player.projectiles) {
            projectile->checkCollision(asteroids);
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
