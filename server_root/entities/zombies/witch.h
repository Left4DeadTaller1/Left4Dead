#ifndef WITCH_H
#define WITCH_H

#include "zombie.h"

enum WitchActionState {
    WITCH_MOVING,
    WITCH_HURT,
    WITCH_DYING,
    WITCH_DEAD,
    WITCH_ATTACKING,
    WITCH_SHOUTING,
    WITCH_IDLE,
};

struct WitchDTO : ZombieDTO {
    WitchActionState actionState;
};

class Witch : public Zombie {
   private:
    WitchActionState actionState;

   public:
    Witch(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto() override;
    int getAttackRange() override;
    Attack attack() override;
    void startMoving() override;
    bool isMoving() override;
    void takeDamage(int damage) override;
    ~Witch();
};

#endif  // WITCH_H