#ifndef ATTACK_H
#define ATTACK_H

#include <string>

enum AttackDirection {
    LEFT,
    RIGHT
};

// TODO: change long and short venom for spray and proyectile
enum AttackType {
    BULLET,
    PIERCING_BULLET,
    MELEE,
    SPEAR_ATTACK,
    SHORT_VENOM,
    LONG_VENOM,
    JUMP,
};

class Attack {
   protected:
    AttackType type;
    int damage;
    int xOrigin;
    AttackDirection direction;
    int lowerY;
    int upperY;
    int range;

    friend class CollisionDetector;

   public:
    Attack(AttackType type, int damage, int xOrigin, int direction, int lowerY, int upperY, int range);
    bool attackingLeft();  // return true if attacking left
    bool attackingRight();
    AttackType getType();
    int getDamage();
    int getRange();
    ~Attack();
};

#endif  // ATTACK_H