#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

struct Vector2
{
    float x, y;
    
    // Get angle in degrees
    float getAngle() const {
        return atan2(y, x) * 180 / M_PI;
    }
    
    // Vector2 * scalar
    Vector2 operator * (float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    
    // Vector2 *= scalar
    Vector2& operator *= (float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    // Vector2 += Vector2
    Vector2& operator += (const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    // Vector2 + Vector2
    Vector2 operator + (const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
};

struct Vector2Int
{
    int x, y;
    
    // Vector2Int * scalar
    Vector2Int operator * (int scalar) const {
        return Vector2Int(x * scalar, y * scalar);
    }
    
    // Vector2Int *= scalar
    Vector2Int& operator *= (int scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    // Vector2Int += Vector2Int
    Vector2Int& operator += (const Vector2Int& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};
