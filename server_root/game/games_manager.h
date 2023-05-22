#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>

#include "game_thread.h"

class GamesManager {
   public:
    GamesManager();

    std::shared_ptr<GameThread> createLobby();

    // method may return a shared pointer to a GameThread (when a GameThread with the given game code is found), or it may return an empty std::optional (when there's no GameThread with the given game code)
    std::optional<std::shared_ptr<GameThread>> joinLobby(unsigned int gameCode);

   private:
    std::unordered_map<int, std::shared_ptr<GameThread>> games;
    std::mutex m;
    int gameId;
};

#endif  // GAME_MANAGER_H
