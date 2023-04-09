#define SDL_MAIN_HANDLED

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <windows.h>

#include "Draw.h"
#include "Entities/Player.cpp"
#include "Entities/Star.cpp"
#include "Entities/Asteroid.cpp"
#include "ScreenInfo.h"

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;

static TTF_Font* font;

bool done = false;
void initSDL();
void doInput();

int main() {
    initSDL();
    srand(time(nullptr));
    
    // Add stars
    for (int i = 0; i < 200; i++) {
        Star* star = new Star(Vector2(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
        Entity::entities.push_back(star);
    }
    
    // Add entities
    auto player = Player();
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
        
        if (!player.remove) {
            auto asteroids = std::vector<Asteroid*>();
            for (auto entity : Entity::entities) {
                if (entity->type == "Asteroid") {
                    asteroids.push_back((Asteroid*)entity);
                }
            }
            for (auto projectile : player.projectiles) {
                if(projectile->checkCollision(asteroids)) {
                    player.score += 100;   
                }
            }
            player.checkCollision(asteroids);
        }

        drawText(renderer, font, "Score: ", Vector2(16, 64), {255, 255, 255});
        drawText(renderer, font, to_string(player.score).c_str(), Vector2(100, 64), {255, 255, 255});
        
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

    if (TTF_Init() < 0) {
        printf("Failed to start SDL_ttf: %s", TTF_GetError());
        exit(-1);
    }
    
    font = TTF_OpenFont("assets/Ubuntu-Regular.ttf", 24);
    if (font == nullptr) {
        printf("Failed to load font: %s", TTF_GetError());
        exit(-1);
    }

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
