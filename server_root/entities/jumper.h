#ifndef JUMPER_H
#define JUMPER_H

#include "zombie.h"

class Jumper : public Zombie {
   private:
    /* data */
   public:
    Jumper(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto();
    int getAttackRange() override;
    Attack attack() override;
    ~Jumper();
};

#endif  // JUMPER_H