#include "attack.h"

Attack::Attack(AttackType type, int damage, int xOrigin, int direction, int lowerY, int upperY, int range) : type(type), damage(damage), xOrigin(xOrigin), lowerY(lowerY), upperY(upperY), range(range) {
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

int Attack::getRange() {
    return range;
}

int Attack::getOrigin() {
    return xOrigin;
}

Attack::~Attack() {}