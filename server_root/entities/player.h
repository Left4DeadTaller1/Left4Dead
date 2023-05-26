#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

#include "entity.h"

class Player : public Entity {
   private:
    std::string idPlayer;

   public:
    Player(int xPosition, int yPosition, int width, int height, std::string idPlayer);
    std::string getId();

    void move(int deltaX, int deltaY);
    ~Player();
};

#endif  // PLAYER_H_