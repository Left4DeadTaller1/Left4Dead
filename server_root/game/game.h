#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>

#include "entity.h"
#include "player.h"

class Game {
   private:
    int idGame;
    bool gameRunning;
    int lastEntityId;
    // Capaz conviene separar los players de los entities pq tienen comportamientos
    // distintos que los zombies.
    //  Todo cambiar a map
    std::vector<std::shared_ptr<Entity>> entities;

   public:
    Game(int idGame, std::vector<Player*>& players);
    void startGameLoop();

    void updateState();
    void moveEntities();

    // The move method should of the game should move all the entities
    // void move(int deltaX, int deltaY, int idPlayer);
};

#endif  // GAME_H_
