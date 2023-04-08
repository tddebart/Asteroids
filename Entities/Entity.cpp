#include "Entity.h"

#include "../Draw.h"


Entity::Entity(SDL_Texture *texture, Vector2 position) {
    this->texture = texture;
    this->position = position;
}

void Entity::update() {

}

void Entity::draw(SDL_Renderer *renderer) {
    drawTexture(renderer, texture, position.x, position.y, angle);
}

