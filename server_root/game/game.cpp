#include "game.h"

#include <algorithm>
#include <chrono>
#include <thread>
#define MAX_QUEUE_SIZE 16000
#define MAX_ACTIONS_PER_FRAME 50

// 1000 ms / 30 FPS = 33.3 ms per frame
#define MS_PER_FRAME 33

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
-------------------Api for clientCommunication------------------
________________________________________________________________*/

Game::Game()
    : inputQueue(MAX_QUEUE_SIZE), nextPlayerIndex(1), gameRunning(false), collisionDetector() {
    playerQueues.resize(4, nullptr);
}

std::string Game::addPlayer(Queue<ServerMessage>& gameResponses) {
    if (nextPlayerIndex >= 4) {
        throw std::out_of_range("Player list is full!");
    }
    // Use nextPlayerIndex to create playerId
    std::string playerId = "Player" + std::to_string(nextPlayerIndex);
    addPlayer(playerId);
    // Use nextPlayerIndex to insert the player queue into playerQueues
    playerQueues[nextPlayerIndex] = &gameResponses;
    nextPlayerIndex++;
    return playerId;
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

void Game::pushAction(Action action) {
    std::cout << "pushAction: action pushed for player " << action.getPlayerId() << std::endl;
    inputQueue.push(action);
}

void Game::run() {
    // Start the game when the thread starts running
    startGame();
}

void Game::sendAction(Action action) {
    // TODO: si usasemos el hash hariamos un push a la queue del player correspondiente pero solo la intencion no la accion en si, el objeto action muere aca, pregunta a gpt si hace falta un delete.
    inputQueue.push(action);
}

void Game::stop() {
    gameRunning = false;
}

bool Game::getGameRunning() {
    return gameRunning;
}

Game::~Game() {}

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
-----------------------Api for Game-----------------------------
________________________________________________________________*/

void Game::addPlayer(std::string playerId) {
    // Here the game should figure out the coordinates of the player for now as placew holder is 0 0 0 0
    auto player = std::make_shared<Player>(0, 0, 0, 0, playerId);
    // Todo: we have to make this match with the id of the player or something.
    entities.push_back(player);
}

void Game::removePlayer(std::string playerId) {
    // erase-remove idiom
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [playerId](const auto& entity) {
                                      Player* player = dynamic_cast<Player*>(entity.get());
                                      return player != nullptr && player->getPlayerId() == playerId;
                                  }),
                   entities.end());
}

void Game::startGame() {
    gameRunning = true;
    std::cout << "startGame: game started" << std::endl;
    while (gameRunning) {
        auto start = std::chrono::steady_clock::now();

        getPlayersActions();

        updateState();  // update game state

        // sendState();     // send the new state to the clients

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (elapsed.count() < MS_PER_FRAME) {
            std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_FRAME) - elapsed);
        }
    }

    gameRunning = false;
    std::cout << "startGame: game stopped" << std::endl;
}

void Game::getPlayersActions() {
    Action playerAction;
    // std::cout << "getPlayersActions: inputQueue size at start: " << inputQueue.size() << std::endl;
    int actionsProcessed = 0;

    for (int i = 0; i < MAX_ACTIONS_PER_FRAME; ++i) {
        if (inputQueue.try_pop(playerAction)) {
            playersActions[playerAction.getPlayerId()].push(playerAction);
            actionsProcessed++;
            std::cout << "getPlayersActions: action popped from inputQueue for player " << playerAction.getPlayerId() << std::endl;
        } else {
            std::cout << "getPlayersActions: no more actions to pop" << std::endl;
            break;
        }
    }
    // std::cout << "getPlayersActions: inputQueue size at end: " << inputQueue.size() << std::endl;
    std::cout << "getPlayersActions: playersActions size at end: " << playersActions.size() << std::endl;
    std::cout << "getPlayersActions: actions processed: " << actionsProcessed << std::endl;
}

void Game::updateState() {
    for (auto& entity : entities) {
        Player* player = dynamic_cast<Player*>(entity.get());
        if (player) {
            std::cout << "updatePlayerState: initial actions count for player " << player->getPlayerId() << ": " << playersActions[player->getPlayerId()].size() << std::endl;
            updatePlayerState(*player, playersActions[player->getPlayerId()]);
        }
        moveEntity(*entity);
    }
}

void Game::updatePlayerState(Player& player, std::queue<Action>& playerActions) {
    while (!playerActions.empty()) {
        Action action = playerActions.front();
        playerActions.pop();
        MovementState movementState = static_cast<MovementState>(action.getMovementType());
        MovementDirectionX movementDirectionX = static_cast<MovementDirectionX>(action.getDirectionXType());
        MovementDirectionY movementDirectionY = static_cast<MovementDirectionY>(action.getDirectionYType());

        player.setMovementState(movementState);
        player.setMovementDirectionX(movementDirectionX);
        player.setMovementDirectionY(movementDirectionY);
    }
}

void Game::moveEntity(Entity& entity) {
    int deltaX = 0;
    int deltaY = 0;
    bool validMovement;
    MovementState movementState = entity.getMovementState();
    MovementDirectionX movementDirectionX = entity.getMovementDirectionX();
    MovementDirectionY movementDirectionY = entity.getMovementDirectionY();
    int movementSpeed = entity.getMovementSpeed();
    // TODO work around this nested if
    if (movementState == ENTITY_WALKING) {
        if (movementDirectionX == ENTITY_LEFT) {
            deltaX = -movementSpeed;
        } else if (movementDirectionX == ENTITY_RIGHT) {
            deltaX = movementSpeed;
        }

        if (movementDirectionY == ENTITY_DOWN) {
            deltaY = -movementSpeed;
        } else if (movementDirectionY == ENTITY_UP) {
            deltaY = movementSpeed;
        }
    } else if (movementState == ENTITY_RUNNING) {
        if (movementDirectionX == ENTITY_LEFT) {
            deltaX = -(2 * movementSpeed);
        } else if (movementDirectionX == ENTITY_RIGHT) {
            deltaX = (2 * movementSpeed);
        }

        if (movementDirectionY == ENTITY_DOWN) {
            deltaY = -(2 * movementSpeed);
        } else if (movementDirectionY == ENTITY_UP) {
            deltaY = (2 * movementSpeed);
        }
    }
    if (movementState != ENTITY_IDLE) {
        validMovement = collisionDetector.checkForCollisions(entity, deltaX, deltaY, entities);
        if (validMovement) {
            entity.move(deltaX, deltaY);
        }
    }
}

const std::unordered_map<std::string, std::queue<Action>>& Game::_getPlayersActions() const {
    return playersActions;
}