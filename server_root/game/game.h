#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>

#include "entity.h"
#include "player.h"

class Game {
   private:
    int idGame;
    int lastEntityId;
    bool gameRunning;
    // Todo cambiar a map
    std::vector<std::shared_ptr<Entity>> entities;

   public:
    Game(int idGame, std::vector<Player*>& players);
    void startGameLoop();

    void updateState();
    
    void moveEntities();

    void processInput();

    void sendState();

    // The move method should of the game should move all the entities
    // void move(int deltaX, int deltaY, int idPlayer);
};

#endif  // GAME_H_
