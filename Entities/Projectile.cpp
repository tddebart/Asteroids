#pragma once

#include "Entity.h"
#include "OffScreenEntity.h"
#include "Asteroid.cpp"
#include <chrono>
#include "Explosion.cpp"

class Projectile : public OffScreenEntity
{
public:
    std::chrono::time_point<std::chrono::system_clock> spawned = std::chrono::system_clock::now();
    
    const float speed = 1.75f;
    const int lifetime = 2000;
    
    Projectile(Vector2 position, int angle) : OffScreenEntity(position) {
        this->angle = angle - 90;
        float rad = this->angle * M_PI / 180.0f;
        velocity = Vector2(cos(rad), sin(rad)) * speed;
        offScreenMargin = 10;
    }

    void update() override {
        position += velocity;
        
        checkOffScreen();
        
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - spawned).count() > lifetime) {
            remove = true;
        }
    }
    
    void draw(SDL_Renderer *renderer) override {
        SDL_SetRenderDrawColor(renderer, 214, 41, 21, 255);
        SDL_RenderDrawLine(renderer, position.x, position.y, position.x + velocity.x*4, position.y + velocity.y*4);
    }
    
    bool checkCollision(const std::vector<Asteroid*>& asteroids) {
        for (auto &asteroid : asteroids) {
            if (asteroid->inside(position + velocity*4)) {
                remove = true;
                asteroid->remove = true;
                
                Entity::entities.push_back(new Explosion(asteroid->position));
                
                if (asteroid->points.size() > 7) {
                    for (int i = 0; i < 2; i++) {
                        Entity::entities.push_back(new Asteroid(asteroid->position + Vector2(rand() % 20 - 10, rand() % 20 - 10), asteroid->angle - 90 - 180 * i, 4,7));
                    }
                }
                
                return true;
            }
        }
        
        return false;
    }
};