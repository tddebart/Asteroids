#include "Entity.h"
#include "../Input.h"

class Player : public Entity {
public:
    using Entity::Entity;

    const float speed = 0.2;

    void update() override {
        if (isKeyPressed(SDL_SCANCODE_W)) {
            velocity.x += speed * sin(angle * M_PI / 180);
            velocity.y -= speed * cos(angle * M_PI / 180);
        }
        if (isKeyPressed(SDL_SCANCODE_S)) {
            velocity.x -= speed * sin(angle * M_PI / 180);
            velocity.y += speed * cos(angle * M_PI / 180);
        }
        if (isKeyPressed(SDL_SCANCODE_A)) {
            angle -= 1;
        }
        if (isKeyPressed(SDL_SCANCODE_D)) {
            angle += 1;
        }

        position += velocity;

        velocity *= 0.98;

        // Teleport to other side of screen
        if (position.x < -50) {
            position.x = SCREEN_WIDTH + 50;
        }
        if (position.x > SCREEN_WIDTH + 50) {
            position.x = -50;
        }
        if (position.y < -50) {
            position.y = SCREEN_HEIGHT + 50;
        }
        if (position.y > SCREEN_HEIGHT + 50) {
            position.y = -50;
        }
    }
};
