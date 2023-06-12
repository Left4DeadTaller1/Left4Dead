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

struct PlayerDTO : EntityDTO {
    WeaponState weaponState;
};

class Player : public Entity {
   private:
    WeaponState weaponState;
    Weapon weapon;

   public:
    Player(int xPosition, int yPosition, std::string idPlayer, WeaponType weapon);

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