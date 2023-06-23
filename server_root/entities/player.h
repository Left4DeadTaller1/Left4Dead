#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

#include "entity.h"
#include "weapon.h"

enum PlayerActionState {
    PLAYER_WALKING,    // 0
    PLAYER_RUNNING,    // 1
    PLAYER_IDLE,       // 2
    PLAYER_SHOOTING,   // 3
    PLAYER_RELOADING,  // 4
    PLAYER_ATTACKING,  // 5
    PLAYER_HURT,       // 6
    PLAYER_DYING,      // 7
    PLAYER_DEAD,       // 8
};

struct PlayerDTO : EntityDTO {
    int bullets;
    PlayerActionState actionState;
};

class Player : public Entity {
   private:
    Weapon weapon;
    PlayerActionState actionState;

   public:
    Player(int xPosition, int yPosition, std::string idPlayer, WeaponType weapon);

    void setMovementDirectionX(MovementDirectionX movementDirectionX);
    void setMovementDirectionY(MovementDirectionY movementDirectionY);

    void setActionState(PlayerActionState actionState);
    PlayerActionState getActionState();

    EntityType getType() override;
    std::shared_ptr<EntityDTO> getDto() override;
    bool isMoving() override;
    void idle() override;
    std::tuple<int, int> getDirectionsAmount();
    void takeDamage(int damage) override;
    void decreaseActionCounter() override;

    void decreaseATKCooldown();

    void reload();
    bool canAttack() override;
    Attack attack();
    void startMoving() override;

    bool checkIfDead() override;
    void kill() override;
    bool isDead() override;
    bool isRemovable() override;
    ~Player();
};

#endif  // PLAYER_H_