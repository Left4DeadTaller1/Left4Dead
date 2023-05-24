#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>

#include "game_thread.h"

class GamesManager {
    // Recordatorio pasale una Queue del Cliente para registrarse a una partida
   private:
    std::unordered_map<int, std::shared_ptr<GameThread>> games;
    std::mutex m;
    int gameId;

   public:
    GamesManager();

    Queue<Action>* createLobby();

    // method may return a reference to the Queue (when a GameThread with the given game code is found), or it may return an empty std::optional (when there's no GameThread with the given game code)
    Queue<Action>* joinLobby(unsigned int gameCode);

    // Method for Testing do not use them in production
    int _getGameId();
    const std::unordered_map<int, std::shared_ptr<GameThread>>& _getGames() const;
};

#endif  // GAME_MANAGER_H
