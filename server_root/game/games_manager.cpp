#include "games_manager.h"

#include <algorithm>
#include <iostream>

GamesManager::GamesManager() : nextGameId(0) {}

GameRecord GamesManager::createLobby(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses, std::string nickName, int weaponType, int typeMap) {
    std::lock_guard<std::mutex> lock(m);
    auto game = std::make_shared<Game>(typeMap);
    games.emplace(nextGameId, game);
    // Creates struct representing game
    GameRecord gameRecord;
    // TODO Catch full lobby exception in Receiver
    gameRecord.playerId = game->addPlayer(gameResponses, nickName, weaponType, nextGameId);
    nextGameId++;
    gameRecord.game = game;
    return gameRecord;
}

void GamesManager::startGame(unsigned int gameCode) {
    std::lock_guard<std::mutex> lock(m);
    auto it = games.find(gameCode);
    if (it != games.end()) {
        it->second->start();
    }
}

GameRecord GamesManager::joinLobby(unsigned int gameCode, Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses, std::string playerNickname, int weaponType) {
    std::lock_guard<std::mutex> lock(m);
    auto it = games.find(gameCode);
    if (it != games.end()) {
        GameRecord gameRecord;
        gameRecord.game = it->second;
        //  Access Game and return a pointer to the inputQueue
        gameRecord.playerId = it->second->addPlayer(gameResponses, playerNickname, weaponType, gameCode);
        return gameRecord;
    }
    return GameRecord{};
}

int GamesManager::_getNextGameId() {
    return nextGameId;
}

const std::unordered_map<int, std::shared_ptr<Game>>& GamesManager::_getGames() const {
    return games;
}

GamesManager::~GamesManager() {
    // Para prevenir problemas de concurrencia
    std::lock_guard<std::mutex> lock(m);

    for (auto& gamePair : games) {
        auto& game = gamePair.second;
        if (game && game->isGameRunning()) {
            game->join();
        }
    }
}
