#include "games_manager.h"

#include <algorithm>
#include <iostream>

GamesManager::GamesManager() : gameId(0) {}

std::reference_wrapper<Queue<Action>> GamesManager::createLobby() {
    std::lock_guard<std::mutex> lock(m);
    auto gameThread = std::make_shared<GameThread>();
    games.emplace(gameId, gameThread);
    gameThread->addPlayer();
    gameId++;
    // Return a reference to the inputQueue
    return std::ref(gameThread->getInputQueue());
}

std::optional<std::reference_wrapper<Queue<Action>>> GamesManager::joinLobby(unsigned int gameCode) {
    std::lock_guard<std::mutex> lock(m);
    auto it = games.find(gameCode);
    if (it != games.end()) {
        // Access GameThread and return a reference to the inputQueue
        it->second->addPlayer();
        return std::ref(it->second->getInputQueue());
    }
    return std::nullopt;
}

int GamesManager::_getGameId() {
    return gameId;
}

const std::unordered_map<int, std::shared_ptr<GameThread>>& GamesManager::_getGames() const {
    return games;
}
