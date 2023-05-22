#include <algorithm>
#include <iostream>

#include "games_manager.h"

GamesManager::GamesManager() : gameId(0) {}

std::shared_ptr<GameThread> GamesManager::createLobby() {
    std::lock_guard<std::mutex> lock(m);
    auto gameThread = std::make_shared<GameThread>();
    games.emplace(gameId, gameThread);
    gameId++;
    return gameThread;
}

std::optional<std::shared_ptr<GameThread>> GamesManager::joinLobby(unsigned int gameCode) {
    std::lock_guard<std::mutex> lock(m);
    auto it = games.find(gameCode);
    if (it != games.end()) {
        return it->second;
    }
    return std::nullopt;
}

// void GamesManager::createGame(unsigned int matchCode, const std::string &scenarioName) {
//     std::unique_lock<std::mutex> lock(m);
//     games.emplace_back(matchCode, scenarioName);
// }
