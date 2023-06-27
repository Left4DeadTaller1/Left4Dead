#ifndef SPEAR_H
#define SPEAR_H

#include "zombie.h"

enum SpearActionState {
    SPEAR_MOVING,
    SPEAR_HURT,
    SPEAR_DYING,
    SPEAR_DEAD,
    SPEAR_ATTACKING,
    SPEAR_IDLE,
};

struct SpearDTO : ZombieDTO {
    SpearActionState actionState;
};

class Spear : public Zombie {
   private:
    SpearActionState actionState;

   public:
    Spear(int xPosition, int yPosition, std::string zombieId, int mutationLevel);
    std::shared_ptr<EntityDTO> getDto() override;
    // int getAttackRange() override;
    Attack generateAttack() override;
    void attackPlayer() override;
    void startMoving() override;
    bool isMoving() override;
    void idle() override;
    bool takeDamage(int damage) override;
    bool checkIfDead() override;
    void kill() override;
    bool isDead() override;
    bool isRemovable() override;

    ~Spear();
};

#endif  // SPEAR_H