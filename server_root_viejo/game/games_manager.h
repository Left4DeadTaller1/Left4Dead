#ifndef GAMES_MANAGER_H
#define GAMES_MANAGER_H

#include <mutex>
#include <vector>
#include <map>
#include "game.h"
#include "queue.h"
#include "game_thread.h"
#include <string>

class GameManager {
    private:
        std::mutex m;
        std::map<int, Game*> gameManager;
        std::map<int, Queue<Action*>*> qActionsGames;
        std::map<int, GameThread*> gamesThread;
        unsigned int contador;

    public:
        explicit GameManager(unsigned int n);

        Game* create(const std::string& name, Queue<std::shared_ptr<gameStateDTO_t>>* qClient, int idEntity);

        //Game* join(int code, Queue<std::shared_ptr<gameStateDTO_t>>* qClient, int idEntity);
        Queue<Action*>* join(int code, Queue<std::shared_ptr<gameStateDTO_t>>* qClient, int idEntity);

        void delete_all_gameManager(void);

        Queue<Action*>* startGame(int code);
};

#endif
