#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include "game.h"
#include "queue.h"
#include "thread.h"
#include "action.h"

#define MS_PER_FRAME 30

class GameThread : public Thread{
    private:
    Game* game;
    Queue<Action*>* qActions;

    public:
    GameThread(Game* game, Queue<Action*>* qActions);

    virtual void run() override;
};

#endif
