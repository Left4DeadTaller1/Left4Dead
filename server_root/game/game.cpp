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

Game::Game(int mapType)
    : inputQueue(MAX_QUEUE_SIZE), nextPlayerIndex(0), gameRunning(false), gameStarted(false), collisionDetector(), protocol(), zombieSpawner(), framesCounter(0), zombiesKilled(0), scoreSaver() {
    if (mapType >= MAP1_BACKGROUND && mapType <= MAP8_BACKGROUND) {
        mapBackground = static_cast<MapType>(mapType);
        createObstacles(mapBackground);
    } else {
        // TODO launch an exception
        std::cout << "Unkown map" << std::endl;
    }

    playerQueues.resize(4, nullptr);
}

void Game::createObstacles(MapType mapBackground) {
    switch (mapBackground) {
        case MAP1_BACKGROUND:
        case MAP2_BACKGROUND: {
            auto crater1 = std::make_shared<Obstacle>(110, 25, "crater1", 40, 160);
            auto crater2 = std::make_shared<Obstacle>(430, 90, "crater2", 40, 120);
            auto crater3 = std::make_shared<Obstacle>(900, 35, "crater3", 50, 260);

            entities.push_back(crater1);
            entities.push_back(crater2);
            entities.push_back(crater3);

            break;
        }
        case MAP7_BACKGROUND:
        case MAP8_BACKGROUND: {
            auto tire1 = std::make_shared<Obstacle>(70, 35, "tire1", 50, 120);
            auto tire2 = std::make_shared<Obstacle>(95, 45, "tire2", 50, 120);
            auto tire3 = std::make_shared<Obstacle>(570, 15, "tire3", 45, 120);
            auto tire4 = std::make_shared<Obstacle>(700, 80, "tire4", 100, 130);
            auto tire5 = std::make_shared<Obstacle>(1115, 60, "tire5", 120, 150);

            entities.push_back(tire1);
            entities.push_back(tire2);
            entities.push_back(tire3);
            entities.push_back(tire4);
            entities.push_back(tire5);

            break;
        }

        default:
            break;
    }
}

std::string Game::addPlayer(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses, std::string playerNickname, int weaponType, int gameCode) {
    if (nextPlayerIndex >= 4) {
        throw std::out_of_range("Player list is full!");
    }
    std::string playerId = "Player" + std::to_string(nextPlayerIndex + 1);
    spawnPlayer(playerId, playerNickname, weaponType);
    playerQueues[nextPlayerIndex] = &gameResponses;

    playersActions[playerId] = std::queue<Action>();
    playerIdToQueueIndex.emplace(playerId, nextPlayerIndex);

    nextPlayerIndex++;

    std::vector<LobbyPlayerDTO> playersInfo;
    for (const std::shared_ptr<Player>& player : players) {
        playersInfo.push_back(player->getLobbyDto());
    }

    int intMapType = static_cast<int>(mapBackground);
    std::shared_ptr<std::vector<uint8_t>> joinMessage = protocol.encodeServerMessage("JoinLobby", intMapType, playersInfo, gameCode);

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
    std::shared_ptr<std::vector<uint8_t>> joinMessage = protocol.encodeServerMessage("GameStarted");
    for (auto playerQueue : playerQueues) {
        if (playerQueue != nullptr) {
            playerQueue->try_push(joinMessage);
        }
    }

    startGame();
}

void Game::sendAction(Action action) {
    inputQueue.push(action);
}

void Game::stop() {
    gameRunning = false;
    closePlayerQueues();
}

bool Game::isGameRunning() {
    return gameRunning;
}

bool Game::hasGameStarted() {
    return gameStarted;
}

bool Game::hasActivePlayers() {
    for (auto queuePtr : playerQueues) {
        if (queuePtr != nullptr) {
            return true;
        }
    }
    return false;
}

void Game::closePlayerQueues() {
    for (auto queuePtr : playerQueues) {
        if (queuePtr) {
            queuePtr->close();
        }
    }
}

void Game::killGame() {
    if (gameRunning == true)
        stop();
}

Game::~Game() {
    std::cout << "Game being destroyed" << std::endl;
}

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
-----------------------Api for Game-----------------------------
________________________________________________________________*/

void Game::spawnPlayer(std::string playerId, std::string nickName, int weaponTypeInput) {
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

    WeaponType weaponType;

    switch (weaponTypeInput) {
        case 0:
            weaponType = SMG;
            break;
        case 1:
            weaponType = RIFLE;
            break;
        case 2:
            weaponType = SNIPER;
            break;

        default:
            weaponType = SMG;
            break;
    }

    auto player = std::make_shared<Player>(spawnX, spawnY, playerId, weaponType, nickName);
    entities.push_back(player);
    players.push_back(player);
}

void Game::removePlayer(Player& playerToRemove) {
    // Find and remove the player from the players vector
    auto it_player = std::find_if(players.begin(), players.end(),
                                  [&playerToRemove](const std::shared_ptr<Player>& p) { return p.get() == &playerToRemove; });

    if (it_player != players.end()) {
        players.erase(it_player);
    }

    // Find and remove the player from the entities list
    auto it_entity = std::find_if(entities.begin(), entities.end(),
                                  [&playerToRemove](const std::shared_ptr<Entity>& e) { return e.get() == &playerToRemove; });

    if (it_entity != entities.end()) {
        entities.erase(it_entity);
    }
}

void Game::startGame() {
    gameStarted = true;
    startTime = std::chrono::steady_clock::now();
    // TODO this is for debuging
    zombieSpawner.increaseTotalZombies();
    int totalZombies = zombieSpawner.getTotalZombies();
    std::string zombieId = "zombie" + std::to_string(totalZombies);
    entities.push_back(std::make_shared<Witch>(100, 50, zombieId, 0));

    gameRunning = true;
    while (gameRunning) {
        auto start = std::chrono::steady_clock::now();

        getPlayersActions();

        updateState();  // update game state

        auto alivePlayersStatus = hasAlivePlayers(players);
        if (alivePlayersStatus.has_value() && !alivePlayersStatus.value()) {
            std::cout << "All players are dead. Closing the game." << std::endl;
            sendScoreScreen();
            stop();
            break;
        } else if (!alivePlayersStatus.has_value() || !hasActivePlayers()) {
            std::cout << "No players left. Closing the game." << std::endl;
            stop();
            break;
        }

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
    std::vector<Player*> playersToRemove;

    for (auto& entity : entities) {
        if (entity->getType() == OBSTACLE)
            continue;

        if (entity->isDead()) {
            entity->decreaseActionCounter();
            continue;
        }

        entity->decreaseActionCounter();
        entity->decreaseATKCooldown();  // yes they need to be 2 separe methods
        Player* player = dynamic_cast<Player*>(entity.get());
        if (player) {
            bool shouldRemove = updatePlayerState(*player, playersActions[player->getId()]);
            if (shouldRemove || checkAfk(*player)) {
                // player was afk or disconnected, and therefore removed
                playersToRemove.push_back(player);
                continue;
            }

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

        performEntitySkill(*entity);
    }

    // remove the afk entities
    for (auto& playerToRemove : playersToRemove) {
        // TODO send a disconection msg to client before removing queue
        disconnectPlayer(*playerToRemove);
    }

    // TODO copy logic from afks
    removeDeadEntities();

    // Every min mutate zombies
    if (framesCounter != 0 && framesCounter % 1800 == 0)
        zombieSpawner.mutate();

    // spawn zombies
    std::shared_ptr<Entity> spawnedZombie = zombieSpawner.spawn();
    if (spawnedZombie) {
        entities.push_back(spawnedZombie);
    }
}

bool Game::updatePlayerState(Player& player, std::queue<Action>& playerActions) {
    if (playerActions.empty()) {
        player.increaseAfkTimer();
        return false;
    } else {
        if (player.getActionCounter() != 0) {
            return false;
        }

        Action action = playerActions.front();
        playerActions.pop();
        player.resetAfkTimer();

        int actionPlayerState = action.getInputType();
        int actionMovementDirectionX = action.getDirectionXType();
        int actionMovementDirectionY = action.getDirectionYType();

        if (actionPlayerState == DISCONNECTION) {
            std::cout << "\nPlayer " << player.getId() << " disconnected." << std::endl;
            return true;
        }

        if (actionPlayerState != NO_CHANGE) {
            PlayerActionState playerState = static_cast<PlayerActionState>(actionPlayerState);

            switch (playerState) {
                case PLAYER_SHOOTING:
                    if (player.canAttack()) {
                        player.setActionState(playerState);
                    }
                    break;

                case PLAYER_REVIVING:
                    if (player.getActionState() != PLAYER_REVIVING) {
                        std::shared_ptr<Player> revivalTarget = player.getClosestRevivablePlayer(players);
                        if (revivalTarget) {
                            player.setClosestRevivablePlayer(revivalTarget);
                            player.setRevivalState();
                        }
                    }
                    break;

                default:
                    player.setActionState(playerState);
                    break;
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

        return false;
    }
}

void Game::reloadPlayer(Player& player) {
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
            if (player->getActionState() == PLAYER_SHOOTING) {
                auto attack = player->generateAttack();
                std::list<std::shared_ptr<Entity>> damagedEntities = collisionDetector.shoot(attack, entities);

                switch (attack.getType()) {
                    case PIERCING_BULLET: {
                        // i mean yeah this prob should be inside the weapon class (Sniper case) but whatever
                        GameConfig& config = GameConfig::getInstance();
                        std::map<std::string, int> weaponsParams = config.getWeaponsParams();
                        int bulletLostDmg = weaponsParams["SNIPER_DMG_LOST_PER_PIERCE"];
                        int enemiesPierced = 0;

                        if (!damagedEntities.empty()) {
                            int effectiveDamage = attack.getDamage() - (bulletLostDmg * enemiesPierced);

                            while (effectiveDamage > 0 && !damagedEntities.empty()) {
                                if (damagedEntities.front()->takeDamage(effectiveDamage))
                                    zombiesKilled++;
                                damagedEntities.pop_front();

                                enemiesPierced++;
                                effectiveDamage = attack.getDamage() - (bulletLostDmg * enemiesPierced);
                            }
                        }

                        break;
                    }
                    default:
                        if (!damagedEntities.empty()) {
                            // TODO Test dmgs
                            int distanceTraveled = abs(attack.getOrigin() - damagedEntities.front()->getX());
                            int effectiveDamage = attack.getDamage() - (distanceTraveled / player->getWeaponDamageFalloff());
                            // Todo change this to bool return
                            if (damagedEntities.front()->takeDamage(effectiveDamage))
                                zombiesKilled++;
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
    if (entity.isDead() && entity.getActionCounter() > 0)
        return;

    std::vector<std::shared_ptr<Entity>> targetEntities(players.begin(), players.end());

    entity.useSkill(targetEntities);
}

void Game::performEntitySkill(Entity& entity) {
    // For now lets just make zombies have abilities
    Zombie* zombie = dynamic_cast<Zombie*>(&entity);
    if (!zombie) {
        return;
    }
    std::shared_ptr<Ability> ability = zombie->getActiveSkill();
    if (!ability) {
        return;
    }

    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    if (ability->type == WAIL_ABILITY && zombie->getActionCounter() == entityParams["WITCH_WAIL_DURATION"]) {
        Witch* witch = dynamic_cast<Witch*>(zombie);
        if (witch == nullptr || witch->getActionState() != WITCH_SHOUTING)
            return;

        int witchWidth = entityParams["WITCH_WIDTH"];
        int witchHeight = entityParams["WITCH_HEIGHT"];
        int infectedWidth = entityParams["INFECTED_WIDTH"];
        int infectedHeight = entityParams["INFECTED_HEIGHT"];
        int mutationLevel = witch->getMutationLevel();

        int leftOfWitch = witch->getX() - infectedWidth - 15;
        int rightOfWitch = witch->getX() + witchWidth + 15;
        int upOfWitch = witch->getY() + witchHeight + 15;
        int downOfWitch = witch->getY() - infectedHeight - 15;

        switch (witch->getMutationLevel()) {
            case 3:
                // Spawn zombie to the top left of the witch
                if (collisionDetector.isEmptySpace(entities, leftOfWitch, upOfWitch)) {
                    zombieSpawner.increaseTotalZombies();
                    int totalZombies = zombieSpawner.getTotalZombies();
                    std::string zombieId = "zombie" + std::to_string(totalZombies);
                    entities.push_back(std::make_shared<Infected>(leftOfWitch, upOfWitch, zombieId, mutationLevel));
                }
            case 2:
                // Spawn zombie to the top right of the witch
                if (collisionDetector.isEmptySpace(entities, rightOfWitch, upOfWitch)) {
                    zombieSpawner.increaseTotalZombies();
                    int totalZombies = zombieSpawner.getTotalZombies();
                    std::string zombieId = "zombie" + std::to_string(totalZombies);
                    entities.push_back(std::make_shared<Infected>(rightOfWitch, upOfWitch, zombieId, mutationLevel));
                }
            case 1:
                // Spawn zombie to the bottom left of the witch
                if (collisionDetector.isEmptySpace(entities, leftOfWitch, downOfWitch)) {
                    zombieSpawner.increaseTotalZombies();
                    int totalZombies = zombieSpawner.getTotalZombies();
                    std::string zombieId = "zombie" + std::to_string(totalZombies);
                    entities.push_back(std::make_shared<Infected>(leftOfWitch, downOfWitch, zombieId, mutationLevel));
                }
            case 0:
                // Spawn zombie to the bottom right of the witch
                if (collisionDetector.isEmptySpace(entities, rightOfWitch, downOfWitch)) {
                    zombieSpawner.increaseTotalZombies();
                    int totalZombies = zombieSpawner.getTotalZombies();
                    std::string zombieId = "zombie" + std::to_string(totalZombies);
                    entities.push_back(std::make_shared<Infected>(rightOfWitch, downOfWitch, zombieId, mutationLevel));
                }
                break;
            default:
                break;
        }
    } else if (ability->type == JUMP_ABILITY && zombie->getActionCounter() > 0) {
        Jumper* jumper = dynamic_cast<Jumper*>(zombie);
        if (!jumper || jumper->getActionState() != JUMPER_JUMPING)
            return;

        GameConfig& config = GameConfig::getInstance();
        std::map<std::string, int> entityParams = config.getEntitiesParams();
        int deltaX = entityParams["JUMPER_JUMP_DISTANCE"] / entityParams["JUMPER_JUMP_DURATION"];
        int deltaY = 0;

        if (jumper->facingLeft()) {
            deltaX = -deltaX;
        }

        // Checks For collisions while jumping
        // TODO REMOVE THE DELTA Y
        std::shared_ptr<Entity> collidedEntity = collisionDetector.collidesWhileJumping(*jumper, deltaX, deltaY, entities);

        if (collidedEntity == nullptr && !jumper->getHasCrashed()) {
            jumper->move(deltaX, deltaY);
        }

        else if (collidedEntity != nullptr && jumper->getHasCrashed()) {
            jumper->startCrashing();
            if (collidedEntity->getType() == PLAYER) {
                int jumpDamage = entityParams["JUMPER_JUMP_DAMAGE"];
                collidedEntity->takeDamage(jumpDamage);
            }
        }
    }
}

const std::unordered_map<std::string, std::queue<Action>>& Game::_getPlayersActions() const {
    return playersActions;
}

bool Game::checkAfk(Player& player) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameParams = config.getGameDimensions();

    if (player.getAfkTimer() >= gameParams["PLAYER_MAX_AFK_TIME"]) {
        std::cout << "Removing Player: " << player.getId() << " for AFK." << std::endl;
        return true;
    }
    return false;
}

void Game::disconnectPlayer(Player& player) {
    auto it = playerIdToQueueIndex.find(player.getId());

    if (it != playerIdToQueueIndex.end()) {
        size_t queueIndex = it->second;

        removePlayer(*playerQueues[queueIndex]);

        playerIdToQueueIndex.erase(it);

        playersActions.erase(player.getId());
    }
    removePlayer(player);
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

std::optional<bool> Game::hasAlivePlayers(std::vector<std::shared_ptr<Player>> players) {
    if (players.empty()) {
        return std::nullopt;
    }

    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    int dyingBeforeGameClose = entityParams["PLAYER_DYING_DURATION"] - 150;

    for (auto& player : players) {
        // Check if the player is not dead
        if (!player->isDead()) {
            // Player is alive, game should continue
            return true;
        } else if (player->getActionState() == PLAYER_DYING && player->getActionCounter() > dyingBeforeGameClose) {
            // Player is dying, but action counter has not reached the threshold, game should continue
            return true;
        }
    }

    // If code reaches here, all players are either dead or in dying state with action counter <= dyingBeforeGameClose
    return false;
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

void Game::sendScoreScreen() {
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime);
    std::chrono::seconds elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed);
    int totalSeconds = elapsedSeconds.count();

    // Get top player scores
    std::string playersNames;
    for (std::vector<std::shared_ptr<Player>>::size_type i = 0; i < players.size(); i++) {
        if (i == players.size() - 1)
            playersNames += players[i]->getNickName();
        else
            playersNames += players[i]->getNickName() + ", ";
    }

    // Save the score entry
    scoreSaver.saveScore(playersNames, zombiesKilled, totalSeconds);

    std::shared_ptr<std::vector<uint8_t>> serializedState = protocol.encodeServerMessage(totalSeconds, zombiesKilled);
    for (Queue<std::shared_ptr<std::vector<uint8_t>>>* playerQueue : playerQueues) {
        if (playerQueue) {
            playerQueue->push(serializedState);
        }
    }
}

std::vector<std::shared_ptr<EntityDTO>> Game::getDtos() {
    std::vector<std::shared_ptr<EntityDTO>> dtos;
    for (auto& entity : entities) {
        if (entity->getType() == OBSTACLE)
            continue;
        auto dto = entity->getDto();
        dtos.push_back(dto);
    }
    return dtos;
}