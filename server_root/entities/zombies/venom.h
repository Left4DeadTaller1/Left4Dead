#ifndef VENOM_H
#define VENOM_H

#include "zombie.h"

enum VenomActionState {
    VENOM_MOVING,
    VENOM_HURT,
    VENOM_DYING,
    VENOM_DEAD,
    VENOM_ATTACKING,
    VENOM_SHOOTING,
    VENOM_IDLE,
};

struct VenomDTO : ZombieDTO {
    VenomActionState actionState;
};

class Venom : public Zombie {
   private:
    VenomActionState actionState;

   public:
    Venom(int xPosition, int yPosition, std::string zombieId);
    std::shared_ptr<EntityDTO> getDto() override;
    int getAttackRange() override;
    Attack attack() override;
    void startMoving() override;
    bool isMoving() override;
    void takeDamage(int damage) override;
    void checkIfDead() override;
    void kill() override;
    bool isDead() override;
    ~Venom();
};

#endif  // VENOM_H