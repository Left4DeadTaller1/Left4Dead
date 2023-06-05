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
    std::string idPlayer;
    WeaponState weaponState;

   public:
    Player(int xPosition, int yPosition, int width, int height, std::string idPlayer);
    std::string getPlayerId();

    void move(int deltaX, int deltaY);
    ~Player();
};

#endif  // PLAYER_H_