#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

#include "entity.h"
#include "shot.h"

enum WeaponState {
    SHOOTING,
    RELOADING,
    WEAPON_IDLE
};

struct PlayerDTO : EntityDTO {
    WeaponState weaponState;
};

class Player : public Entity {
   private:
    // TODO: move id to Entity
    WeaponState weaponState;
    int bullets;

   public:
    Player(int xPosition, int yPosition, int width, int height, std::string idPlayer);

    EntityType getType() override;
    WeaponState getWeaponState();
    void setWeaponState(WeaponState weaponState);
    std::shared_ptr<EntityDTO> getDto() override;

    void decreaseAtkCooldown();

    bool canAttack() override;
    Shot shoot();
    ~Player();
};

#endif  // PLAYER_H_