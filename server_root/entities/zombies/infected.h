#ifndef INFECTED_H
#define INFECTED_H

#include "zombie.h"

class Infected : public Zombie {
   private:
    /* data */
   public:
    Infected(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto();
    int getAttackRange() override;
    Attack attack() override;
    ~Infected();
};

#endif  // INFECTED_H
