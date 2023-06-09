#ifndef ATTACK_H
#define ATTACK_H

#include <string>

enum AttackDirection {
    LEFT,
    RIGHT
};

enum AttackType {
    BULLET,
    PIERCING_BULLET,
    MELEE,
    SPEAR_ATTACK,
    SHORT_VENOM,
    LONG_VENOM,
};

class Attack {
   protected:
    AttackType type;
    int damage;
    int xOrigin;
    AttackDirection direction;
    int lowerY;
    int upperY;

    friend class CollisionDetector;

   public:
    Attack(AttackType type, int damage, int xOrigin, int direction, int lowerY, int upperY);
    bool attackingLeft();  // return true if attacking left
    bool attackingRight();
    AttackType getType();
    int getDamage();
    ~Attack();
};

#endif  // ATTACK_H