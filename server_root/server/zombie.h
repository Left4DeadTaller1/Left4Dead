#ifndef ZOMBIE_H
#define ZOMBIE_H
#define ATK_COOLDOWN 10  // TODO think this in relation with fps game loop

#include <string>

#include "entity.h"

class Zombie : public Entity {
   private:
    int atkCooldown;

   public:
    // Constructor
    Zombie(int xPosition, int yPosition, int width, int height);
    ~Zombie();

    void attack();  // added attack function declaration here
};

#endif  // ZOMBIE_H
