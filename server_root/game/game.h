#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include "entity.h"
#include "player.h"

class Game {
   private:
    int idGame;
    // Player player;
    std::vector<Player*>& players;

   public:
    Game(int idGame, std::vector<Player*>& players);

    void move(int deltaX, int deltaY, int idPlayer);
};

#endif  // GAME_H_
