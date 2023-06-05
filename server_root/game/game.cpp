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
    : inputQueue(MAX_QUEUE_SIZE), nextPlayerIndex(1), gameRunning(false), collisionDetector() {
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
    entities.push_back(player);
}

void Game::removePlayer(std::string idPlayer) {
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

void Game::getPlayersActions() {
    Action playerAction;
    // std::cout << "getPlayersActions: inputQueue size at start: " << inputQueue.size() << std::endl;
    int actionsProcessed = 0;

    for (int i = 0; i < MAX_ACTIONS_PER_FRAME; ++i) {
        if (inputQueue.try_pop(playerAction)) {
            playersActions[playerAction.getPlayerId()].push(playerAction);
            actionsProcessed++;
        } else {
            break;
        }
    }
}

void Game::updateState() {
    for (auto& entity : entities) {
        Player* player = dynamic_cast<Player*>(entity.get());
        if (player) {
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
