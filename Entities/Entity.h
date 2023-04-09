#pragma once

#include "../Vector2.h"
#include <SDL.h>
#include <string>
#include <vector>

class Entity {
public:
    inline static std::vector<Entity*> entities;
    
    Vector2 position = Vector2(0, 0);
    Vector2 velocity = Vector2(0, 0);
    int angle = 0;
    SDL_Texture *texture = nullptr;
    bool remove = false;
    std::string type = "Entity";

    explicit Entity(SDL_Texture *texture = nullptr, Vector2 position = Vector2(0, 0));

    virtual void update();

    virtual void draw(SDL_Renderer *renderer);
};
