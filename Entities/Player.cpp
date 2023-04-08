#include "Entity.h"
#include "../Input.h"
#include "Projectile.cpp"
#include <chrono>

#define PLAYER_SIZE 52

class Player : public Entity {
public:
    using Entity::Entity;

    std::vector<Projectile> projectiles;
    
    const float speed = 0.1f;
    
    std::chrono::time_point<std::chrono::system_clock> lastShot = std::chrono::system_clock::now();

    void update() override {
        input();

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
        
        for (auto &projectile : projectiles) {
            projectile.update();
        }
        
        auto item = std::find_if(projectiles.begin(), projectiles.end(), [](Projectile &projectile) {
            return projectile.position.x < 0 || projectile.position.x > SCREEN_WIDTH || projectile.position.y < 0 || projectile.position.y > SCREEN_HEIGHT;
        });
        
        if (item != projectiles.end()) {
            projectiles.erase(item);
        }
    }
    
    void draw(SDL_Renderer *renderer) override {
        for (auto &projectile : projectiles) {
            projectile.draw(renderer);
        }
        
        Entity::draw(renderer);
    }
    
    void input() {
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
        
        if (isKeyPressed(SDL_SCANCODE_SPACE) && std::chrono::system_clock::now() - lastShot > std::chrono::milliseconds(200)) {
            projectiles.emplace_back(position + Vector2(PLAYER_SIZE/2.0f, PLAYER_SIZE/2.0f), angle);
            lastShot = std::chrono::system_clock::now();
        }
    }
};
