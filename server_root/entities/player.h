#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

#include "entity.h"
#include "weapon.h"

enum PlayerActionState {
    PLAYER_WALKING,
    PLAYER_RUNNING,
    PLAYER_IDLE,
    PLAYER_SHOOTING,
    PLAYER_RELOADING,
    PLAYER_ATTACKING,
    PLAYER_HURT,
    PLAYER_DYING,
    PLAYER_DEAD,
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
    std::tuple<int, int> getDirectionsAmount();
    void takeDamage(int damage) override;

    void decreaseATKCooldown();

    bool canAttack() override;
    Attack attack();

    void checkIfDead() override;
    void kill() override;
    bool isDead() override;
    bool isRemovable() override;
    ~Player();
};

#endif  // PLAYER_H_