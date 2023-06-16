#ifndef VENOM_H
#define VENOM_H

#include "zombie.h"

class Venom : public Zombie {
   private:
    /* data */
   public:
    Venom(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto();
    int getAttackRange() override;
    Attack attack() override;
    ~Venom();
};

#endif  // VENOM_H