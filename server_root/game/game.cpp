#include "game.h"

#include <algorithm>
#include <chrono>
#include <thread>
#define MAX_QUEUE_SIZE 16000

// 1000 ms / 30 FPS = 33.3 ms per frame
#define MS_PER_FRAME 33

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
-------------------Api for clientCommunication------------------
________________________________________________________________*/

Game::Game()
    : inputQueue(MAX_QUEUE_SIZE), alive(true), gameRunning(false), nextPlayerIndex(0) {
    playerQueues.resize(4, nullptr);
}

std::string Game::addPlayer(Queue<ServerMessage>& gameResponses) {
    if (nextPlayerIndex >= 4) {
        throw std::out_of_range("Player list is full!");
    }
    // Use nextPlayerIndex to create idPlayer
    std::string idPlayer = "Player" + std::to_string(nextPlayerIndex);
    addPlayer(idPlayer);
    // Use nextPlayerIndex to insert the player queue into playerQueues
    playerQueues[nextPlayerIndex] = &gameResponses;
    nextPlayerIndex++;
    return idPlayer;
}

void Game::removePlayer(Queue<ServerMessage>& gameResponses) {
    // Find the player queue in playerQueues
    auto it = std::find(playerQueues.begin(), playerQueues.end(), &gameResponses);
    if (it != playerQueues.end()) {
        // If the player queue is found, replace it with nullptr
        int index = std::distance(playerQueues.begin(), it);
        playerQueues[index] = nullptr;

        // Adjust nextPlayerIndex if necessary
        if (index < nextPlayerIndex) {
            nextPlayerIndex = index;
        }
    } else {
        throw std::invalid_argument("Player not found in game!");
    }
}

Queue<Action>& Game::getInputQueue() {
    return inputQueue;
}

std::vector<Queue<ServerMessage>*>& Game::_getPlayerQueues() {
    return playerQueues;
}

void Game::run() {
    while (alive) {
        // lobby logic;
    }
    alive = false;
}

void Game::sendAction(Action action) {
    // TODO: si usasemos el hash hariamos un push a la queue del player correspondiente pero solo la intencion no la accion en si, el objeto action muere aca, pregunta a gpt si hace falta un delete.
    inputQueue.push(action);
}

void Game::stop() {
    gameRunning = false;
    alive = false;
}

Game::~Game() {}

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
-----------------------Api for Game-----------------------------
________________________________________________________________*/

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

void Game::startGame() {
    gameRunning = true;
    while (gameRunning) {
        auto start = std::chrono::steady_clock::now();

        // getPlayerActions();  // asks game thread for the actions of the players and stores it in the hash

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

void Game::updateState() {
    // We update the state of the game
}

