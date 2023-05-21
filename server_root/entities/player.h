#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include "entity.h"

class Player : public Entity {
   private:
    int idPlayer;

   public:
    Player(int xPosition, int yPosition, int width, int height, int idPlayer);

    void move(int deltaX, int deltaY);
};

#endif  // PLAYER_H_