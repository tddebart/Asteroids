#ifndef SHOOT_UP_2D_ENTITY_H
#define SHOOT_UP_2D_ENTITY_H

#include "../Vector2.h"
#include <SDL.h>

class Entity {
public:
    Vector2 position = Vector2(0, 0);
    Vector2 velocity = Vector2(0, 0);
    int angle = 0;
    SDL_Texture *texture = nullptr;
    bool remove = false;

    explicit Entity(SDL_Texture *texture = nullptr, Vector2 position = Vector2(0, 0));

    virtual void update();

    virtual void draw(SDL_Renderer *renderer);
};

#endif //SHOOT_UP_2D_ENTITY_H
