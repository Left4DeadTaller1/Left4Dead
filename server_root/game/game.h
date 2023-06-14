#ifndef GAME_H_
#define GAME_H_

#include <queue>
#include <unordered_map>

#include "action.h"
#include "collision_detector.h"
#include "entity.h"
#include "player.h"
#include "queue.h"
#include "server_message.h"
#include "server_protocol.h"
#include "thread.h"
#include "zombie.h"
#include "zombie_spawner.h"

// change to Game
class Game : public Thread {
    /*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
    -------------------Api for clientCommunication------------------
    ________________________________________________________________*/
   private:
    // This is the big Queue where all the clients push their actions
    Queue<Action> inputQueue;
    std::vector<Queue<std::shared_ptr<std::vector<uint8_t>>>*> playerQueues;
    int nextPlayerIndex;

   public:
    explicit Game();
    void run() override;
    std::string addPlayer(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses);
    void removePlayer(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses);
    Queue<Action>& getInputQueue();

    // Later add the API for the clients to push actions to the InputQueue
    void pushAction(Action action);

    void startGame();
    void sendAction(Action action);
    void stop();
    bool getGameRunning();
    // leaveGame();

    ~Game();

    // Methods for Testing do not use in production
    std::vector<Queue<std::shared_ptr<std::vector<uint8_t>>>*>& _getPlayerQueues();

    /*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
    -----------------------Api for Game-----------------------------
    ________________________________________________________________*/
   private:
    bool gameRunning;
    CollisionDetector collisionDetector;
    std::unordered_map<std::string, std::queue<Action>>
        playersActions;
    std::vector<std::shared_ptr<Player>> players;
    // std::vector<std::shared_ptr<Zombie>> zombies;
    std::vector<std::shared_ptr<Entity>> entities;
    ServerProtocol protocol;
    ZombieSpawner zombieSpawner;

    void spawnPlayer(std::string idPlayer);
    void removePlayer(std::string idPlayer);
    void updateState();
    void updatePlayerState(Player& player, std::queue<Action>& playerActions);
    void move(Entity& entity);
    void attack(Entity& entity);
    void getPlayersActions();

    void sendState();
    std::vector<std::shared_ptr<EntityDTO>> getDtos();

   public:
    // Methods for Testing do not use in production
    const std::unordered_map<std::string, std::queue<Action>>& _getPlayersActions() const;
};

#endif  // GAME_H_
