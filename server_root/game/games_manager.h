#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>

#include "game.h"
#include "server_message.h"

struct GameRecord {
    std::string playerId;
    std::shared_ptr<Game> game;
};

class GamesManager {
    // Recordatorio pasale una Queue del Cliente para registrarse a una partida
   private:
    std::unordered_map<int, std::shared_ptr<Game>> games;
    std::mutex m;
    int gameId;

   public:
    GamesManager();

    GameRecord createLobby(Queue<ServerMessage>& gameResponses);

    // method may return a reference to the Queue (when a Game with the given game code is found), or it may return an empty std::optional (when there's no Game with the given game code)
    GameRecord joinLobby(unsigned int gameCode, Queue<ServerMessage>& gameResponses);

    // Method for Testing do not use them in production
    int _getGameId();
    const std::unordered_map<int, std::shared_ptr<Game>>& _getGames() const;
};

#endif  // GAME_MANAGER_H
