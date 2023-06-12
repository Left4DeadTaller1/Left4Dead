#include "attack.h"

Attack::Attack(AttackType type, int damage, int xOrigin, int direction, int lowerY, int upperY) : type(type), damage(damage), xOrigin(xOrigin), lowerY(lowerY), upperY(upperY) {
    if (direction == 0) {
        this->direction = LEFT;
    } else {
        this->direction = RIGHT;
    }
}

bool Attack::attackingLeft() {
    return direction == LEFT;
}

bool Attack::attackingRight() {
    return direction == RIGHT;
}

AttackType Attack::getType() {
    return type;
}

int Attack::getDamage() {
    return damage;
}

Attack::~Attack() {}