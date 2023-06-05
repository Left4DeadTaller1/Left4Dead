#ifndef GAME_H_
#define GAME_H_

#include <queue>  // add this for std::queue

#include "action.h"
#include "entity.h"
#include "player.h"
#include "queue.h"
#include "server_message.h"
#include "thread.h"


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
    bool alive;

   public:
    explicit Game();
    void run() override;
    std::string addPlayer(Queue<ServerMessage>& gameResponses);
    void removePlayer(Queue<ServerMessage>& gameResponses);
    Queue<Action>& getInputQueue();

    // Later add the API for the clients to push actions to the InputQueue

    void startGame();
    void sendAction(Action action);
    void stop();
    // leaveGame();


    ~Game();

    // Methods for Testing do not use in production
    std::vector<Queue<ServerMessage>*>& _getPlayerQueues();

    /*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
    -----------------------Api for Game-----------------------------
    ________________________________________________________________*/
   private:
    bool gameRunning;
    std::vector<std::shared_ptr<Entity>> entities;

    void addPlayer(std::string idPlayer);
    void removePlayer(std::string idPlayer);
    void updateState();
};

#endif  // GAME_H_
