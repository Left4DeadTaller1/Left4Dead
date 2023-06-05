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
#include "thread.h"
#include "zombie.h"

// change to Game
class Game : public Thread {
    /*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
    -------------------Api for clientCommunication------------------
    ________________________________________________________________*/
   private:
    // This is the big Queue where all the clients push their actions
    Queue<Action> inputQueue;
    // vector of player queues TODO: change this to make it size 4, consider using hash
    std::vector<Queue<ServerMessage>*> playerQueues;
    int nextPlayerIndex;

   public:
    explicit Game();
    void run() override;
    std::string addPlayer(Queue<ServerMessage>& gameResponses);
    void removePlayer(Queue<ServerMessage>& gameResponses);
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
    std::vector<Queue<ServerMessage>*>& _getPlayerQueues();

    /*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
    -----------------------Api for Game-----------------------------
    ________________________________________________________________*/
   private:
    bool gameRunning;
    CollisionDetector collisionDetector;
    std::unordered_map<std::string, std::queue<Action>>
        playersActions;
    // std::vector<std::shared_ptr<Player>> players;
    // std::vector<std::shared_ptr<Zombie>> zombies;
    std::vector<std::shared_ptr<Entity>> entities;

    void addPlayer(std::string idPlayer);
    void removePlayer(std::string idPlayer);
    void updateState();
    void updatePlayerState(Player player, std::queue<Action> playerActions);
    void moveEntity(Entity& entity);
    void getPlayersActions();

   public:
    // Methods for Testing do not use in production
    const std::unordered_map<std::string, std::queue<Action>>& _getPlayersActions() const;
};

#endif  // GAME_H_
