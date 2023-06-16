#ifndef SPEAR_H
#define SPEAR_H

#include "zombie.h"

class Spear : public Zombie {
   private:
    /* data */
   public:
    Spear(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto();
    int getAttackRange() override;
    Attack attack() override;
    ~Spear();
};

#endif  // SPEAR_H