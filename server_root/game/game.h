#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <string>
#include <vector>

#include "entity.h"
#include "player.h"

class Game {
   private:
    bool gameRunning;

    // Capaz conviene separar los players de los entities pq tienen comportamientos distintos que los zombies. (este si un vector)
    // TODO: this should be a list since adding and removing element is more expensive in a vector than a list for example.
    std::vector<std::shared_ptr<Entity>> entities;

   public:
    Game();
    void addPlayer(std::string idPlayer);
    void removePlayer(std::string idPlayer);
    void startGameLoop();

    void updateState();
    void moveEntities();

    // The move method should of the game should move all the entities
    // void move(int deltaX, int deltaY, int idPlayer);
};

#endif  // GAME_H_
