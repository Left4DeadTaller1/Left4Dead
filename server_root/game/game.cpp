#include "game.h"

#include <algorithm>
#include <chrono>
#include <thread>

// 1000 ms / 30 FPS = 33.3 ms per frame
#define MS_PER_FRAME 33

Game::Game() : gameRunning(false) {
}

void Game::addPlayer(std::string idPlayer) {
    // Here the game should figure out the coordinates of the player for now as placew holder is 0 0 0 0
    auto player = std::make_shared<Player>(0, 0, 0, 0, idPlayer);
    // Todo: we have to make this match with the id of the player or something.
    entities.push_back(player);
}

void Game::removePlayer(std::string idPlayer) {
    // erase-remove idiom
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [idPlayer](const auto& entity) {
                                      Player* player = dynamic_cast<Player*>(entity.get());
                                      return player != nullptr && player->getId() == idPlayer;
                                  }),
                   entities.end());
}

void Game::startGameLoop() {
    gameRunning = true;
    while (gameRunning) {
        auto start = std::chrono::steady_clock::now();

        // processInput();  // process input from the Users

        updateState();  // update game state

        // sendState();     // send the new state to the clients

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (elapsed.count() < MS_PER_FRAME) {
            std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_FRAME) - elapsed);
        }
    }

    gameRunning = false;
}

// void Game::processInput() {
// We process the input from the users
// for (auto& player : players) {
//     player->();
// }
// }

// void Game::sendState() {
// Create DTO Object;
// protocol.sendState(DTO);
// }

void Game::updateState() {
    // We update the state of the game
    moveEntities();
}

// this should be moveZombies()
void Game::moveEntities() {
    // for (auto& zombie : zombies) {
    //     zombie->move();
    // }
}

// void Game::move(int deltaX, int deltaY, int idPlayer) {
//     players[idPlayer]->move(deltaX, deltaY);
// }
