#include "Vector2.h"

class Entity {
public:
    Vector2 position;
    SDL_Texture *texture = nullptr;
    
    Entity(SDL_Texture *texture) {
        this->texture = texture;
    }

    void update() {
        
    }
};
