#ifndef GAME_THREAD_H_
#define GAME_THREAD_H_

#include <queue>  // add this for std::queue

#include "action.h"
#include "game.h"
#include "queue.h"
#include "thread.h"

class GameThread : public Thread {
   private:
    Game game;
    // This is the big Queue where all the clients push their actions
    Queue<Action> inputQueue;
    // vector of player queues
    std::vector<std::queue<int>> playerQueues;  // int as placeholder for GameStateDTO
                                                // std::vector<std::queue<GameStateDTO>> playerQueues;
   public:
    explicit GameThread();
    void run() override;
    void addPlayer();

    void startGame();
    void stop();
    // leaveGame();

    ~GameThread();
};

#endif  // GAME_THREAD_H_
