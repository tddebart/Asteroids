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
    bool remove = false;
    std::string type = "Entity";

    explicit Entity(Vector2 position = Vector2(0, 0));

    virtual void update();

    virtual void draw(SDL_Renderer *renderer);
};
