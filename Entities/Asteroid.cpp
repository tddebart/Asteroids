#pragma once

#include "Entity.h"
#include "OffScreenEntity.h"
#include <vector>

class Asteroid : public OffScreenEntity {
public:
    std::vector<Vector2> points;
    
    explicit Asteroid(Vector2 position, int angle = rand() % 360, int minPoints = 7, int maxPoints = 14) : OffScreenEntity(position) {
        this->angle = angle;
        type = "Asteroid";
        float rad = this->angle * M_PI / 180.0f;
        this->velocity = Vector2(cos(rad), sin(rad)) * 0.5;
        
        int numPoints = rand() % (maxPoints - minPoints) + minPoints;
        
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
    
    bool inside(Vector2 point) {
        int intersections = 0;
        
        for (int i = 0; i < points.size(); i++) {
            Vector2 p1 = points[i] + position;
            Vector2 p2 = points[(i + 1) % points.size()] + position;
            
            if (p1.y > point.y != p2.y > point.y) {
                float x = (point.y - p1.y) / (p2.y - p1.y) * (p2.x - p1.x) + p1.x;
                if (x > point.x) {
                    intersections++;
                }
            }
        }
        
        return intersections % 2 == 1;
    }
};