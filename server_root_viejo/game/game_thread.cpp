#include "game_thread.h"

#define CANT_ACTION_LOOP 50

GameThread::GameThread(Game* game, Queue<Action*>* qActions):game(game),
                                                qActions(qActions) {}

void GameThread::run() {
    while(true){
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < CANT_ACTION_LOOP; i++){
            Action* action;
            bool exito = qActions->try_pop(action);
            if(exito){
                action->run(*game);
            }
        }
        game->update();
        game->sendStateGame();

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (elapsed.count() < MS_PER_FRAME) {
            std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_FRAME) - elapsed);
        }
    }
}
