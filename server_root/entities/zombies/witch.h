#ifndef WITCH_H
#define WITCH_H

#include "zombie.h"

enum WitchActionState {
    WITCH_MOVING,     // 0
    WITCH_HURT,       // 1
    WITCH_DYING,      // 2
    WITCH_DEAD,       // 3
    WITCH_ATTACKING,  // 4
    WITCH_SHOUTING,   // 5
    WITCH_IDLE,       // 6
};

struct WitchDTO : ZombieDTO {
    WitchActionState actionState;
};

class Witch : public Zombie {
   private:
    WitchActionState actionState;

   public:
    Witch(int xPosition, int yPosition, std::string zombieId, int mutationLevel);
    std::shared_ptr<EntityDTO> getDto() override;
    Attack generateAttack() override;
    void attackPlayer() override;
    void startMoving() override;
    void useSkill(std::vector<std::shared_ptr<Entity>> &players);
    std::shared_ptr<Ability> getActiveSkill();
    bool isMoving() override;
    void idle() override;
    void takeDamage(int damage) override;
    bool checkIfDead() override;
    void kill() override;
    bool isDead() override;
    bool isRemovable() override;
    ~Witch();

    void setActionState(WitchActionState actionState);
    WitchActionState getActionState();
};

#endif  // WITCH_H