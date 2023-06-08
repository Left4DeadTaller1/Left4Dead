#ifndef SHOT_H
#define SHOT_H

#include <string>

class CollisionDetector;

enum type {
    SMG,
    RIFLE,
    SNIPER
};

class Shot {
   private:
    bool piercing;
    int damage;
    int xOrigin;
    std::string direction;
    int lowerY;
    int upperY;

    friend class CollisionDetector;

   public:
    Shot(bool piercing,
         int damage,
         int xOrigin,
         std::string direction,
         int lowerY,
         int upperY);
    ~Shot();

    bool shootingLeft();  // return true if shooting left
    bool shootingRight();
    int getDamage();
};

#endif  // SHOT_H
