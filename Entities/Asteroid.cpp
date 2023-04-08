#include "Entity.h"
#include "OffScreenEntity.h"
#include <vector>

class Asteroid : public OffScreenEntity {
public:
    std::vector<Vector2> points;
    
    explicit Asteroid(Vector2 position) : OffScreenEntity(nullptr, position) {
        this->angle = rand() % 360;
        float rad = this->angle * M_PI / 180.0f;
        velocity = Vector2(cos(rad), sin(rad)) * 0.5;
        
        int numPoints = rand() % 5 + 5;
        
        for (int i = 0; i < numPoints; i++) {
            float angle = (float)i / numPoints * 360;
            float rad = angle * M_PI / 180.0f;
            float radius = rand() % 20 + 10;
            points.push_back(Vector2(cos(rad) * radius, sin(rad) * radius));
        }
    }
    
    void update() override {
        position += velocity;
        
        checkOffScreen();
    }
    
    void draw(SDL_Renderer *renderer) override {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        for (int i = 0; i < points.size(); i++) {
            Vector2 point = points[i];
            Vector2 nextPoint = points[(i + 1) % points.size()];
            
            SDL_RenderDrawLine(renderer, position.x + point.x, position.y + point.y, position.x + nextPoint.x, position.y + nextPoint.y);
        }
    }
};