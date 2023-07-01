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

void GamesManager::startGame(std::shared_ptr<Game> gameToStart) {
    std::lock_guard<std::mutex> lock(m);

    // Search for the game in the map based on the shared_ptr.
    for (auto& gamePair : games) {
        if (gamePair.second == gameToStart) {
            gamePair.second->start();
            return;
        }
    }

    // Optional: Print a message if the game was not found in the map.
    std::cout << "Game not found\n";
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

void GamesManager::removeFinishedGames() {
    std::lock_guard<std::mutex> lock(m);
    try {
        for (auto it = games.begin(); it != games.end();) {
            auto& gamePtr = it->second;
            if (!gamePtr->isGameRunning() && gamePtr->hasGameStarted()) {
                std::cout << "Game: " << it->first << " finished, removing it." << std::endl;

                std::cout << "Reference count before erasing: " << gamePtr.use_count() << std::endl;

                gamePtr->join();

                it = games.erase(it);  // erase returns the next iterator so no increase here
                std::cout << "Finished removing game." << std::endl;
            } else {
                ++it;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }
}

void GamesManager::killGames() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [gameId, game] : games) {
        game->killGame();
        game->join();
    }
    games.clear();  // Remove all games from the map
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
