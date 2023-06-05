#include "games_manager.h"

#include <algorithm>
#include <iostream>

GamesManager::GamesManager() : gameId(0) {}

GameRecord GamesManager::createLobby(Queue<ServerMessage>& gameResponses) {
    std::lock_guard<std::mutex> lock(m);
    auto game = std::make_shared<Game>();
    games.emplace(gameId, game);
    gameId++;
    // Creates struct representing game
    GameRecord gameRecord;
    gameRecord.playerId = game->addPlayer(gameResponses);
    gameRecord.game = game;
    return gameRecord;
}

GameRecord GamesManager::joinLobby(unsigned int gameCode, Queue<ServerMessage>& gameResponses) {
    std::lock_guard<std::mutex> lock(m);
    auto it = games.find(gameCode);
    if (it != games.end()) {
        GameRecord gameRecord;
        gameRecord.game = it->second;
        // Access Game and return a pointer to the inputQueue
        gameRecord.playerId = it->second->addPlayer(gameResponses);
        return gameRecord;
    }
    return GameRecord{};
}

int GamesManager::_getGameId() {
    return gameId;
}

const std::unordered_map<int, std::shared_ptr<Game>>& GamesManager::_getGames() const {
    return games;
}
