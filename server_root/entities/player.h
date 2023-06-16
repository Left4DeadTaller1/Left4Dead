#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

#include "entity.h"
#include "weapon.h"

enum WeaponState {
    SHOOTING,
    RELOADING,
    WEAPON_IDLE
};

enum PlayerActionState {
    SHOOTING_STATE,
    RELOADING_STATE,
    ATTACKING_STATE,
    IDLE_STATE,
};

struct PlayerDTO : EntityDTO {
    WeaponState weaponState;
    int bullets;
    PlayerActionState actionState;
};

class Player : public Entity {
   private:
    WeaponState weaponState;
    Weapon weapon;
    PlayerActionState actionState;

   public:
    Player(int xPosition, int yPosition, std::string idPlayer, WeaponType weapon);

    void setMovementState(MovementState movementState);
    void setMovementDirectionX(MovementDirectionX movementDirectionX);
    void setMovementDirectionY(MovementDirectionY movementDirectionY);

    EntityType getType() override;
    WeaponState getWeaponState();
    void setWeaponState(WeaponState weaponState);
    std::shared_ptr<EntityDTO> getDto() override;

    void decreaseATKCooldown();

    bool canAttack() override;
    Attack attack();
    ~Player();
};

#endif  // PLAYER_H_