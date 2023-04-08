#include "Entity.h"

#ifndef SHOOT_UP_2D_OFFSCREENENTITY_H
#define SHOOT_UP_2D_OFFSCREENENTITY_H


class OffScreenEntity: public Entity {
public:
    using Entity::Entity;
    
    int offScreenMargin = 50;
    
    void checkOffScreen();
};


#endif //SHOOT_UP_2D_OFFSCREENENTITY_H
