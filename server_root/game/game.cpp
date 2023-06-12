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
    : inputQueue(MAX_QUEUE_SIZE), nextPlayerIndex(0), gameRunning(false), collisionDetector(), protocol() {
    playerQueues.resize(4, nullptr);
}

std::string Game::addPlayer(Queue<std::vector<uint8_t>>& gameResponses) {
    if (nextPlayerIndex >= 4) {
        throw std::out_of_range("Player list is full!");
    }
    std::string playerId = "Player" + std::to_string(nextPlayerIndex + 1);
    addPlayer(playerId);
    playerQueues[nextPlayerIndex] = &gameResponses;

    playersActions[playerId] = std::queue<Action>();
    nextPlayerIndex++;

    std::vector<uint8_t> joinMessage = protocol.encodeServerMessage("JoinMsg", playerId);

    // Add message to all player queues that are not null
    for (auto playerQueue : playerQueues) {
        if (playerQueue != nullptr) {
            // I use try_push to not block GameThread but maybe this is wrong.
            bool success = playerQueue->try_push(joinMessage);
        }
    }

    return playerId;
}

void Game::removePlayer(Queue<std::vector<uint8_t>>& gameResponses) {
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

std::vector<Queue<std::vector<uint8_t>>*>& Game::_getPlayerQueues() {
    return playerQueues;
}

void Game::pushAction(Action action) {
    inputQueue.push(action);
}

void Game::run() {
    // Start the game when the thread starts running
    startGame();
}

void Game::sendAction(Action action) {
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
    // TODO:Here the game should figure out the coordinates of the player for now as placew holder is 0 0 0 0 and what weapon give him
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameDimensions = config.getGameDimensions();
    int gameWidth = gameDimensions["GAME_WIDTH"];
    int gameHeight = gameDimensions["GAME_HEIGHT"];

    auto player = std::make_shared<Player>(0, 0, playerId, SMG);
    entities.push_back(player);
}

void Game::removePlayer(std::string playerId) {
    // erase-remove idiom
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [playerId](const auto& entity) {
                                      Player* player = dynamic_cast<Player*>(entity.get());
                                      return player != nullptr && player->getId() == playerId;
                                  }),
                   entities.end());
}

void Game::startGame() {
    gameRunning = true;
    while (gameRunning) {
        auto start = std::chrono::steady_clock::now();

        getPlayersActions();

        updateState();  // update game state

        sendState();  // send the new state to the clients

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
    int actionsProcessed = 0;

    for (int i = 0; i < MAX_ACTIONS_PER_FRAME; ++i) {
        if (inputQueue.try_pop(playerAction)) {
            playersActions[playerAction.getId()].push(playerAction);
            actionsProcessed++;
        } else {
            break;
        }
    }
}

void Game::updateState() {
    // Decrementamos DYINGCOUNTER de cada entidad que este en DYING y si este llega a 0 borralo

    for (auto& entity : entities) {
        Player* player = dynamic_cast<Player*>(entity.get());
        if (player) {
            updatePlayerState(*player, playersActions[player->getId()]);
        }
        // else {
        // TODO: remember to decrease entity atk cd
        // }
        move(*entity);
        attack(*entity);
    }
}

void Game::updatePlayerState(Player& player, std::queue<Action>& playerActions) {
    while (!playerActions.empty()) {
        Action action = playerActions.front();
        playerActions.pop();
        MovementState movementState = static_cast<MovementState>(action.getMovementType());
        MovementDirectionX movementDirectionX = static_cast<MovementDirectionX>(action.getDirectionXType());
        MovementDirectionY movementDirectionY = static_cast<MovementDirectionY>(action.getDirectionYType());
        WeaponState weaponState = static_cast<WeaponState>(action.getWeaponState());

        player.setMovementState(movementState);
        player.setMovementDirectionX(movementDirectionX);
        player.setMovementDirectionY(movementDirectionY);
        player.setWeaponState(weaponState);
        player.decreaseATKCooldown();
    }
}

void Game::move(Entity& entity) {
    int deltaX = 0;
    int deltaY = 0;
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
    if (movementState != ENTITY_IDLE)
        if (!collisionDetector.checkForCollisions(entity, deltaX, deltaY, entities))
            entity.move(deltaX, deltaY);
}

void Game::attack(Entity& entity) {
    if (entity.canAttack()) {
        std::unique_ptr<Attack> attackPtr = nullptr;

        if (entity.getType() == PLAYER) {
            attackPtr = std::make_unique<Attack>(dynamic_cast<Player&>(entity).attack());
        } else if (entity.getType() == ZOMBIE) {
            attackPtr = std::make_unique<Attack>(dynamic_cast<Zombie&>(entity).attack());
        }

        if (attackPtr) {
            std::list<std::shared_ptr<Entity>> damagedEntities = collisionDetector.beingAttack(*attackPtr, entities);

            switch (attackPtr->getType()) {
                case PIERCING_BULLET:
                    // code
                    break;

                default:
                    if (!damagedEntities.empty()) {
                        damagedEntities.front()->takeDamage(attackPtr->getDamage());
                    }
                    break;
            }
        }
    }
}

const std::unordered_map<std::string, std::queue<Action>>& Game::_getPlayersActions() const {
    return playersActions;
}

void Game::sendState() {
    std::vector<std::shared_ptr<EntityDTO>> entitiesDtos = getDtos();
    std::vector<uint8_t> serializedState = protocol.encodeServerMessage("gameState", entitiesDtos);

    for (Queue<std::vector<uint8_t>>* playerQueue : playerQueues) {
        if (playerQueue) {
            playerQueue->push(serializedState);
        }
    }
}

std::vector<std::shared_ptr<EntityDTO>> Game::getDtos() {
    std::vector<std::shared_ptr<EntityDTO>> dtos;
    for (auto& entity : entities) {
        auto dto = entity->getDto();
        dtos.push_back(dto);
    }
    return dtos;
}
