﻿#include "Entity.h"
#include "../Input.h"
#include "Projectile.cpp"
#include "../ScreenInfo.h"

#include <chrono>

#define PLAYER_SIZE 32

using namespace std;

class Player : public Entity {
public:
    using Entity::Entity;

    std::vector<Projectile*> projectiles;
    
    std::vector<Vector2> points = {
            Vector2(0, -PLAYER_SIZE),
            Vector2(PLAYER_SIZE, PLAYER_SIZE),
            Vector2(0, PLAYER_SIZE / 2.0f),
            Vector2(-PLAYER_SIZE, PLAYER_SIZE)
    };
    
    std::vector<Vector2> flamePoints = {
            Vector2(0, PLAYER_SIZE / 2.0f),
            Vector2(PLAYER_SIZE / 2.0f, PLAYER_SIZE),
            Vector2(0, PLAYER_SIZE * 0.75),
            Vector2(-PLAYER_SIZE / 2.0f, PLAYER_SIZE)
    };
    
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
            projectile->update();
            
            if (projectile->remove) {
                projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
            }
        }
    }
    
    void draw(SDL_Renderer *renderer) override {
        for (auto &projectile : projectiles) {
            projectile->draw(renderer);
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        drawPoints(renderer, points, position, angle);
        if (isKeyPressed(SDL_SCANCODE_W)) {
            drawPoints(renderer, flamePoints, position, angle);
        }
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
            projectiles.push_back(new Projectile(position + Vector2(PLAYER_SIZE/2.0f, PLAYER_SIZE/2.0f), angle));
            lastShot = std::chrono::system_clock::now();
        }
    }
};
