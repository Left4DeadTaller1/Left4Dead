#include "games_manager.h"

#include <algorithm>
#include <iostream>

GamesManager::GamesManager() : gameId(0) {}

std::shared_ptr<GameThread> GamesManager::createLobby() {
    std::lock_guard<std::mutex> lock(m);
    auto gameThread = std::make_shared<GameThread>();
    games.emplace(gameId, gameThread);
    gameThread->addPlayer();
    gameId++;
    return gameThread;
}

std::optional<std::shared_ptr<GameThread>> GamesManager::joinLobby(unsigned int gameCode) {
    std::lock_guard<std::mutex> lock(m);
    auto it = games.find(gameCode);
    if (it != games.end()) {
        // access GameThread
        it->second->addPlayer();
        return it->second;
    }
    return std::nullopt;
}

int GamesManager::_getGameId() {
    return gameId;
}

const std::unordered_map<int, std::shared_ptr<GameThread>>& GamesManager::_getGames() const {
    return games;
}
