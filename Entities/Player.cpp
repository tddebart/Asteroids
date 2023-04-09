#pragma once

#include "Entity.h"
#include "../Input.h"
#include "Projectile.cpp"
#include "../ScreenInfo.h"
#include "Asteroid.cpp"

#include <chrono>

#define PLAYER_SIZE 16

using namespace std;

class Player : public Entity {
public:

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
    
    const float speed = 0.05f;
    int score = 0;
    int lives = 3;
    
    std::chrono::time_point<std::chrono::system_clock> lastShot = std::chrono::system_clock::now();
    
    Player() : Entity(Vector2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f)) {
    }

    void update() override {
        input();

        position += velocity;

        velocity *= 0.99f;

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
        
        // Draw lives
        for (int i = 0; i < lives; i++) {
            drawPoints(renderer, points, Vector2(PLAYER_SIZE * 2 + i * (PLAYER_SIZE + 5) * 2, PLAYER_SIZE * 2), 0);
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
            projectiles.push_back(new Projectile(position, angle));
            lastShot = std::chrono::system_clock::now();
        }
    }
    
    void checkCollision(const std::vector<Asteroid*>& asteroids) {
        for (auto &asteroid : asteroids) {
            for (auto &point : points) {
                auto newPoint = point;
                newPoint.rotate(angle);
                newPoint += position;
                
                if (asteroid->inside(newPoint)) {
                    lives--;
                    Entity::entities.push_back(new Explosion(position));
                    position = Vector2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
                    velocity = Vector2(0, 0);
                    
                    if (lives <= 0) {
                        remove = true;
                    }
                }
            }
        }
    }
};
