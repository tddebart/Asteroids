#include "Entity.h"

class Projectile : public Entity
{
public:
    Projectile(Vector2 position, int angle) : Entity(nullptr, position) {
        this->angle = angle - 90;
        float rad = this->angle * M_PI / 180.0f;
        velocity = Vector2(cos(rad), sin(rad)) * 1.2;
    }

    void update() override {
        position += velocity;
    }
    
    void draw(SDL_Renderer *renderer) override {
        SDL_SetRenderDrawColor(renderer, 214, 41, 21, 255);
        SDL_RenderDrawLine(renderer, position.x, position.y, position.x + velocity.x*4, position.y + velocity.y*4);
    }
};