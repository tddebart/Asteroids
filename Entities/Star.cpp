#include "Entity.h"

class Star : public Entity {
public:
    float speed;

    Star(SDL_Texture *texture, Vector2 position) : Entity(texture, position) {
        this->speed = ((float)rand() / RAND_MAX) * 3 + 0.25f;
    }
    
    void update() override {
        position.y -= speed;
        if (position.y < 0) {
            position.y = SCREEN_HEIGHT;
        }
    }
    
    void draw(SDL_Renderer *renderer) override {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, position.x, position.y);
    }
};