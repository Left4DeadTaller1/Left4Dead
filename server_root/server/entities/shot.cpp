#include "shot.h"

Shot::Shot(bool piercing,
           int damage,
           int xOrigin,
           std::string direction,
           int lowerY,
           int upperY)
    : piercing(piercing),
      damage(damage),
      xOrigin(xOrigin),
      direction(direction),
      lowerY(lowerY),
      upperY(upperY) {
}

Shot::~Shot() {
}

bool Shot::shootingLeft() {
    return direction == "left";
}
