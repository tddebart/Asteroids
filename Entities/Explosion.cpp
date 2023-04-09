#include "Entity.h"
#include <chrono>
#include <vector>

struct Explosion : public Entity {
    std::vector<Vector2> cubes;
    int cubeSize = 0;

    std::chrono::time_point<std::chrono::system_clock> spawned = std::chrono::system_clock::now();
    const int lifetime = 500;
    
    explicit Explosion(Vector2 position) : Entity(nullptr, position) {
        const int cubeCount = rand() % 4 + 4;
        for (int i = 0; i < cubeCount; i++) {
            cubes.push_back(Vector2(rand() % 10 - 5, rand() % 10 - 5));
        }
        this->cubeSize = rand() % 2 + 4;
        type = "Explosion";
    }
    
    void update() override {
        
        // Move cubes away from center
        for (auto &cube : cubes) {
            cube += cube.getNormalized() * 0.25f;
        }
        
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - spawned).count() > lifetime) {
            remove = true;
        }
    }
    
    void draw(SDL_Renderer *renderer) override {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (auto &cube : cubes) {
            SDL_Rect rect = {static_cast<int>(position.x + cube.x), static_cast<int>(position.y + cube.y), cubeSize, cubeSize};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    
    
};