#include "Draw.h"
#include <vector>

void drawPoints(SDL_Renderer *renderer, std::vector<Vector2> points, Vector2 position, int angle) {
    for (int i = 0; i < points.size(); i++) {
        Vector2 point = points[i];
        Vector2 nextPoint = points[(i + 1) % points.size()];
        
        point.rotate(angle);
        nextPoint.rotate(angle);
        
        SDL_RenderDrawLine(renderer, position.x + point.x, position.y + point.y, position.x + nextPoint.x, position.y + nextPoint.y);
    }
}
