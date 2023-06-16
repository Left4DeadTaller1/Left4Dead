#ifndef WITCH_H
#define WITCH_H

#include "zombie.h"

class Witch : public Zombie {
   private:
    /* data */
   public:
    Witch(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto();
    int getAttackRange() override;
    Attack attack() override;
    ~Witch();
};

#endif  // WITCH_H