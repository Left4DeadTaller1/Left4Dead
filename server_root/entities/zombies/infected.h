#ifndef INFECTED_H
#define INFECTED_H

#include "zombie.h"

enum InfectedActionState {
    INFECTED_MOVING,
    INFECTED_IDLE,
    INFECTED_HURT,
    INFECTED_ATTACKING,
    INFECTED_DYING,
    INFECTED_DEAD,
};

struct InfectedDTO : ZombieDTO {
    InfectedActionState actionState;
};

class Infected : public Zombie {
   private:
    InfectedActionState actionState;

   public:
    Infected(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto() override;
    int getAttackRange() override;
    Attack attack() override;
    void takeDamage(int damage) override;
    void startMoving() override;
    bool isMoving() override;
    void checkIfDead() override;
    void kill() override;
    bool isRemovable() override;
    bool isDead() override;
    ~Infected();
};

#endif  // INFECTED_H
