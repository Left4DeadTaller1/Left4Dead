#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

#include "entity.h"

enum WeaponState {
    SHOOTING,
    RELOADING,
    WEAPON_IDLE
};

class Player : public Entity {
   private:
    // TODO: move id to Entity
    WeaponState weaponState;

   public:
    Player(int xPosition, int yPosition, int width, int height, std::string idPlayer);

    std::string getType() override;
    WeaponState getWeaponState();
    ~Player();
};

#endif  // PLAYER_H_