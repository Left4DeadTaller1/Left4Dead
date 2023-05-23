#ifndef GAMES_MANAGER_H
#define GAMES_MANAGER_H

#include <mutex>
#include <vector>
#include <map>
#include "server_game.h"
#include <string>

class GamesManager {
    private:
        std::mutex m;
        std::map<int, Game*> games;
        unsigned int contador;

    public:
        explicit GamesManager(unsigned int n);

        int create(const std::string& name, Queue<std::string>* queue);

        int join(int code, Queue<std::string>* queue);

        void delete_all_games(void);
};

#endif //GAMES_MANAGER_H