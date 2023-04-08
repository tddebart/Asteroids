#include "OffScreenEntity.h"
#include "../ScreenInfo.h"


void OffScreenEntity::checkOffScreen() {
    // Teleport to other side of screen
    if (position.x < -offScreenMargin) {
        position.x = SCREEN_WIDTH + offScreenMargin;
    }
    if (position.x > SCREEN_WIDTH + offScreenMargin) {
        position.x = -offScreenMargin;
    }
    if (position.y < -offScreenMargin) {
        position.y = SCREEN_HEIGHT + offScreenMargin;
    }
    if (position.y > SCREEN_HEIGHT + offScreenMargin) {
        position.y = -offScreenMargin;
    }
}
