#include "game.h"

#include <algorithm>
#include <chrono>
#include <thread>

#include "game_config.h"
#define MAX_QUEUE_SIZE 16000
#define MAX_ACTIONS_PER_FRAME 50

// 1000 ms / 30 FPS = 33.3 ms per frame
#define MS_PER_FRAME 33

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
-------------------Api for clientCommunication------------------
________________________________________________________________*/

Game::Game()
    : inputQueue(MAX_QUEUE_SIZE), nextPlayerIndex(0), gameRunning(false), collisionDetector(), protocol(), zombieSpawner(), framesCounter(0) {
    playerQueues.resize(4, nullptr);
}

std::string Game::addPlayer(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses, std::string playerNickname) {
    if (nextPlayerIndex >= 4) {
        throw std::out_of_range("Player list is full!");
    }
    std::string playerId = "Player" + std::to_string(nextPlayerIndex + 1);
    spawnPlayer(playerId, playerNickname);
    playerQueues[nextPlayerIndex] = &gameResponses;

    playersActions[playerId] = std::queue<Action>();
    nextPlayerIndex++;

    std::shared_ptr<std::vector<uint8_t>> joinMessage = protocol.encodeServerMessage("JoinMsg", playerId);

    // Add message to all player queues that are not null
    for (auto playerQueue : playerQueues) {
        if (playerQueue != nullptr) {
            playerQueue->try_push(joinMessage);
        }
    }

    return playerId;
}

void Game::removePlayer(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses) {
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

std::vector<Queue<std::shared_ptr<std::vector<uint8_t>>>*>& Game::_getPlayerQueues() {
    return playerQueues;
}

void Game::pushAction(Action action) {
    inputQueue.push(action);
}

void Game::run() {
    // Start the game when the thread starts running
    /*std::shared_ptr<std::vector<uint8_t>> joinMessage = protocol.encodeServerMessage();
    for (auto playerQueue : playerQueues) {
        if (playerQueue != nullptr) {
            playerQueue->try_push(joinMessage);
        }
    }*/

    startGame();
}

void Game::sendAction(Action action) {
    inputQueue.push(action);
}

void Game::stop() {
    gameRunning = false;
}

bool Game::isGameRunning() {
    return gameRunning;
}

Game::~Game() {}

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
-----------------------Api for Game-----------------------------
________________________________________________________________*/

void Game::spawnPlayer(std::string playerId, std::string nickName) {
    // TODO: Here the game should figure out what weapon give each player
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameDimensions = config.getGameDimensions();
    int gameWidth = gameDimensions["GAME_WIDTH"];
    int gameHeight = gameDimensions["GAME_HEIGHT"];

    std::map<std::string, int> playerMeasures = config.getEntitiesParams();
    int playerWidth = playerMeasures["PLAYER_WIDTH"];
    int playerHeight = playerMeasures["PLAYER_HEIGHT"];
    int numPlayers = entities.size();

    int spawnX = gameWidth / 2 + (numPlayers % 2 == 0 ? playerWidth : 0);
    int spawnY = gameHeight / 2 - (numPlayers / 2) * playerHeight;

    auto player = std::make_shared<Player>(spawnX, spawnY, playerId, SNIPER, nickName);
    entities.push_back(player);
    players.push_back(player);
}

void Game::removePlayer(std::string playerId) {
    // erase-remove idiom
    entities.remove_if([playerId](const auto& entity) {
        Player* player = dynamic_cast<Player*>(entity.get());
        return player != nullptr && player->getId() == playerId;
    });
}

void Game::startGame() {
    // TODO debuging
    // zombieSpawner.increaseTotalZombies();
    // int totalZombies = zombieSpawner.getTotalZombies();
    // std::string zombieId = "zombie" + std::to_string(totalZombies);
    // entities.push_back(std::make_shared<Witch>(100, 50, zombieId, 0));

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

        framesCounter++;
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
    // todo: i think this is not efficient and should go int o the if in line 181
    removeDeadEntities();
    for (auto& entity : entities) {
        if (entity->isDead()) {
            entity->decreaseActionCounter();
            continue;
        }

        entity->decreaseActionCounter();
        entity->decreaseATKCooldown();  // yes they need to be 2 separe methods
        Player* player = dynamic_cast<Player*>(entity.get());
        if (player) {
            updatePlayerState(*player, playersActions[player->getId()]);
            // TODO: add a perform method that checks the state of entity
            reloadPlayer(*player);
            revivePlayer(*player);
        }

        else {
            Zombie* zombie = dynamic_cast<Zombie*>(entity.get());
            zombie->decideTarget(players);
        }

        // performAction(*entity)

        move(*entity);
        // TODO change this so the dmg is made if actionCounter is 0
        attack(*entity);
        useSkill(*entity);
    }

    // Every min mutate zombies
    if (framesCounter != 0 && framesCounter % 1800 == 0)
        zombieSpawner.mutate();

    // spawn zombies
    std::shared_ptr<Entity> spawnedZombie = zombieSpawner.spawn();
    if (spawnedZombie) {
        entities.push_back(spawnedZombie);
    }
}

void Game::updatePlayerState(Player& player, std::queue<Action>& playerActions) {
    while (!playerActions.empty()) {
        if (player.getActionCounter() != 0) {
            continue;
        }
        Action action = playerActions.front();
        playerActions.pop();

        int actionPlayerState = action.getInputType();
        int actionMovementDirectionX = action.getDirectionXType();
        int actionMovementDirectionY = action.getDirectionYType();

        if (actionPlayerState == DISCONNECTION) {
            removePlayer(player.getId());
            break;
        }
        if (actionPlayerState != NO_CHANGE) {
            if (actionPlayerState == INPUT_SHOOTING) {
                if (player.canAttack()) {
                    PlayerActionState playerState = static_cast<PlayerActionState>(actionPlayerState);
                    player.setActionState(playerState);
                } else if (actionPlayerState == INPUT_REVIVE) {
                    if (player.getActionState() != PLAYER_REVIVING) {
                        std::shared_ptr<Player> revivalTarget = player.getClosestRevivablePlayer(players);

                        if (revivalTarget) {
                            player.setClosestRevivablePlayer(revivalTarget);
                            player.setRevivalState();
                        }
                    }
                } else {
                    PlayerActionState playerState = static_cast<PlayerActionState>(actionPlayerState);
                    player.setActionState(playerState);
                }
            }

            if (actionMovementDirectionX != NO_CHANGE_X) {
                MovementDirectionX movementDirectionX = static_cast<MovementDirectionX>(actionMovementDirectionX);
                player.setMovementDirectionX(movementDirectionX);
            }
            if (actionMovementDirectionY != NO_CHANGE_Y) {
                MovementDirectionY movementDirectionY = static_cast<MovementDirectionY>(actionMovementDirectionY);
                player.setMovementDirectionY(movementDirectionY);
            }

            if (player.isMoving() && player.getMovementDirectionX() == ENTITY_NONE_X && player.getMovementDirectionY() == ENTITY_NONE_Y) {
                player.idle();
            }

        } else {
            break;
        }
    }
}

void Game::reloadPlayer(Player& player) {
    // TODO: CHANGE THIS SO YOU RELOAD IN FRAME 1
    if (player.getActionState() == PLAYER_RELOADING && player.getActionCounter() == 0) {
        player.reload();
    }
}

void Game::revivePlayer(Player& player) {
    if (player.getActionState() == PLAYER_REVIVING && player.getActionCounter() == 1) {
        player.getRevivingPlayer()->revive();
    }
}

void Game::move(Entity& entity) {
    if (!entity.isMoving())
        return;

    int deltaX = 0;
    int deltaY = 0;

    std::tie(deltaX, deltaY) = entity.getDirectionsAmount();

    int realDeltaX = 0;
    int realDeltaY = 0;

    std::tie(realDeltaX, realDeltaY) = collisionDetector.checkForCollisions(entity, deltaX, deltaY, entities);

    entity.move(realDeltaX, realDeltaY);
}

void Game::attack(Entity& entity) {
    if (entity.canAttack()) {
        if (entity.getType() == PLAYER) {
            Player* player = dynamic_cast<Player*>(&entity);
            // TODO; change this to gral state
            if (player->getActionState() == PLAYER_SHOOTING) {
                auto attack = player->generateAttack();
                std::list<std::shared_ptr<Entity>> damagedEntities = collisionDetector.shoot(attack, entities);

                switch (attack.getType()) {
                    case PIERCING_BULLET: {
                        // i mean yeah this prob should be inside the weapon class (Sniper case) but whatever
                        GameConfig& config = GameConfig::getInstance();
                        std::map<std::string, int> weaponsParams = config.getWeaponsParams();
                        int bulletLostDmg = weaponsParams["SNIPER_DMG_LOST_PER_PIERCE"];
                        int enemiesPierce = 0;

                        if (!damagedEntities.empty()) {
                            int effectiveDamage = attack.getDamage() - (bulletLostDmg * enemiesPierce);

                            while (effectiveDamage > 0 && !damagedEntities.empty()) {
                                damagedEntities.front()->takeDamage(effectiveDamage);
                                damagedEntities.pop_front();

                                enemiesPierce++;
                                effectiveDamage = attack.getDamage() - (bulletLostDmg * enemiesPierce);
                            }
                        }

                        break;
                    }
                    default:
                        if (!damagedEntities.empty()) {
                            // TODO make the takeDamage for ALL zombies
                            damagedEntities.front()->takeDamage(attack.getDamage());
                        }
                        break;
                }
            }
        } else if (entity.getType() == ZOMBIE) {
            Zombie* zombie = dynamic_cast<Zombie*>(&entity);
            auto attack = zombie->generateAttack();
            int attackRange = attack.getRange();
            std::shared_ptr<Player> playerInRange = collisionDetector.getPlayersInRange(attackRange, attack, players);
            if (playerInRange) {
                zombie->attackPlayer();
                playerInRange->takeDamage(attack.getDamage());
            }
        }
    }
}

void Game::useSkill(Entity& entity) {
    if (entity.isDead())
        return;
    std::shared_ptr<Ability> ability = entity.useSkill();
    switch (ability->type) {
        case WAIL: {
            std::shared_ptr<Wail> wailAbility = std::dynamic_pointer_cast<Wail>(ability);
            if (wailAbility) {
                GameConfig& config = GameConfig::getInstance();
                std::map<std::string, int> entitiesDimensions = config.getEntitiesParams();
                int witchWidth = entitiesDimensions["WITCH_WIDTH"];
                int witchHeight = entitiesDimensions["WITCH_HEIGHT"];
                int infectedWidth = entitiesDimensions["INFECTED_WIDTH"];
                int infectedHeight = entitiesDimensions["INFECTED_HEIGHT"];

                int leftOfWitch = wailAbility->WitchX - infectedWidth - 15;
                int rightOfWitch = wailAbility->WitchX + witchWidth + 15;
                int upOfWitch = wailAbility->WitchY + witchHeight + 15;
                int downOfWitch = wailAbility->WitchY - infectedHeight - 15;

                switch (wailAbility->witchInfectionLevel) {
                    case 3:
                        // Spawn zombie to the top left of the witch
                        if (collisionDetector.isEmptySpace(entities, leftOfWitch, upOfWitch)) {
                            zombieSpawner.increaseTotalZombies();
                            int totalZombies = zombieSpawner.getTotalZombies();
                            std::string zombieId = "zombie" + std::to_string(totalZombies);
                            entities.push_back(std::make_shared<Infected>(leftOfWitch, upOfWitch, zombieId, wailAbility->witchInfectionLevel));
                        }
                    case 2:
                        // Spawn zombie to the top right of the witch
                        if (collisionDetector.isEmptySpace(entities, rightOfWitch, upOfWitch)) {
                            zombieSpawner.increaseTotalZombies();
                            int totalZombies = zombieSpawner.getTotalZombies();
                            std::string zombieId = "zombie" + std::to_string(totalZombies);
                            entities.push_back(std::make_shared<Infected>(rightOfWitch, upOfWitch, zombieId, wailAbility->witchInfectionLevel));
                        }
                    case 1:
                        // Spawn zombie to the bottom left of the witch
                        if (collisionDetector.isEmptySpace(entities, leftOfWitch, downOfWitch)) {
                            zombieSpawner.increaseTotalZombies();
                            int totalZombies = zombieSpawner.getTotalZombies();
                            std::string zombieId = "zombie" + std::to_string(totalZombies);
                            entities.push_back(std::make_shared<Infected>(leftOfWitch, downOfWitch, zombieId, wailAbility->witchInfectionLevel));
                        }
                    case 0:
                        // Spawn zombie to the bottom right of the witch
                        if (collisionDetector.isEmptySpace(entities, rightOfWitch, downOfWitch)) {
                            zombieSpawner.increaseTotalZombies();
                            int totalZombies = zombieSpawner.getTotalZombies();
                            std::string zombieId = "zombie" + std::to_string(totalZombies);
                            entities.push_back(std::make_shared<Infected>(rightOfWitch, downOfWitch, zombieId, wailAbility->witchInfectionLevel));
                        }
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        default:
            break;
    }
}

const std::unordered_map<std::string, std::queue<Action>>& Game::_getPlayersActions() const {
    return playersActions;
}

void Game::removeDeadEntities() {
    auto it = entities.begin();
    while (it != entities.end()) {
        if ((*it)->isRemovable()) {
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::sendState() {
    std::vector<std::shared_ptr<EntityDTO>> entitiesDtos = getDtos();
    std::shared_ptr<std::vector<uint8_t>> serializedState = protocol.encodeServerMessage("gameState", entitiesDtos);

    for (Queue<std::shared_ptr<std::vector<uint8_t>>>* playerQueue : playerQueues) {
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