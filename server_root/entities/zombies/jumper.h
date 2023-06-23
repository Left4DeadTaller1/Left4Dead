#ifndef JUMPER_H
#define JUMPER_H

#include "zombie.h"

enum JumperActionState {
    JUMPER_MOVING,
    JUMPER_HURT,
    JUMPER_DYING,
    JUMPER_DEAD,
    JUMPER_ATTACKING,
    JUMPER_JUMPING,
    JUMPER_IDLE,
};

struct JumperDTO : ZombieDTO {
    JumperActionState actionState;
};

class Jumper : public Zombie {
   private:
    JumperActionState actionState;

   public:
    Jumper(int xPosition, int yPosition, std::string zombieId, int mutationLevel);
    std::shared_ptr<EntityDTO> getDto() override;
    // int getAttackRange() override;
    Attack attack() override;
    void startMoving() override;
    void takeDamage(int damage) override;
    bool isMoving() override;
    void idle() override;
    bool checkIfDead() override;
    void kill() override;
    bool isDead() override;
    bool isRemovable() override;
    ~Jumper();
};

#endif  // JUMPER_H