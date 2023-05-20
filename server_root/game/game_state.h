#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <vector>

#include "player.h"

class GameState {
   private:
    int idGame;
    // Player player;
    std::vector<Player*>& players;  // creqie que los jugadores tienen que ir en el heap

   public:
    GameState(int idGame, std::vector<Player*>& players);

    void move(int deltaX, int deltaY, int idPlayer);
};

#endif  // GAME_STATE_H_
