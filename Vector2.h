struct Vector2
{
    float x, y;
    
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
