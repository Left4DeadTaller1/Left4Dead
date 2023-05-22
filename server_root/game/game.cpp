#include "game.h"

#include <chrono>
#include <thread>
// 1000 ms / 30 FPS = 33.3 ms per frame
#define MS_PER_FRAME 33

Game::Game(int idGame, std::vector<Player*>& players) : idGame(idGame),
                                                        gameRunning(false),
                                                        lastEntityId(1) {
    // We add the players to the entities vector
    for (auto& player : players) {
        entities.push_back(std::make_shared<Player>(*player));
    }
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

void Game::moveEntities() {
    for (auto& entity : entities) {
        entity->move();
    }
}

// void Game::move(int deltaX, int deltaY, int idPlayer) {
//     players[idPlayer]->move(deltaX, deltaY);
// }
