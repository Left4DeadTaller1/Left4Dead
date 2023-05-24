#include "games_manager.h"

#include <algorithm>
#include <iostream>

GamesManager::GamesManager() : gameId(0) {}

Queue<Action>* GamesManager::createLobby(Queue<int>& gameResponses) {
    std::lock_guard<std::mutex> lock(m);
    auto gameThread = std::make_shared<GameThread>();
    games.emplace(gameId, gameThread);
    gameThread->addPlayer(gameResponses);
    gameId++;
    // Return a pointer to the inputQueue
    return &(gameThread->getInputQueue());
}

Queue<Action>* GamesManager::joinLobby(unsigned int gameCode, Queue<int>& gameResponses) {
    std::lock_guard<std::mutex> lock(m);
    auto it = games.find(gameCode);
    if (it != games.end()) {
        // Access GameThread and return a pointer to the inputQueue
        it->second->addPlayer(gameResponses);
        return &(it->second->getInputQueue());
    }
    return nullptr;
}

int GamesManager::_getGameId() {
    return gameId;
}

const std::unordered_map<int, std::shared_ptr<GameThread>>& GamesManager::_getGames() const {
    return games;
}
