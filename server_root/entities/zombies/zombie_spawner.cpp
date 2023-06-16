#include "zombie_spawner.h"

#include <cstdlib>

#include "game_config.h"

#define TYPES_OF_ZOMBIE 5

// TODO set the spawnInterval with config yaml
ZombieSpawner::ZombieSpawner() : totalZombies(0) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameDimensions = config.getGameDimensions();
    std::map<std::string, int> spawnSettings = config.getSpawnsParams();

    spawnInterval = spawnSettings["SPAWN_INTERVAL"];

    int gameWidth = gameDimensions["GAME_WIDTH"];
    int gameHeight = gameDimensions["GAME_HEIGHT"];
    // Left spawners
    SpawnPoint spawnPoint1 = {0, (gameHeight + 1)};
    SpawnPoint spawnPoint2 = {0, (2 * gameHeight / 3)};

    // Right spawners
    SpawnPoint spawnPoint3 = {(gameWidth - 100), (gameHeight + 1)};
    SpawnPoint spawnPoint4 = {(gameWidth - 100), (2 * gameHeight / 3)};

    spawnPoints.push_back(spawnPoint1);
    spawnPoints.push_back(spawnPoint2);
    spawnPoints.push_back(spawnPoint3);
    spawnPoints.push_back(spawnPoint4);
}

std::shared_ptr<Entity> ZombieSpawner::spawn() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> spawnSettings = config.getSpawnsParams();
    spawnInterval -= 1;
    if (spawnInterval > 0) {
        return nullptr;
    }

    int spawnPointToSpawn = rand() % spawnPoints.size();

    int spawnX = spawnPoints[spawnPointToSpawn].x;
    int spawnY = spawnPoints[spawnPointToSpawn].y;

    totalZombies += 1;
    std::string zombieId = "zombie" + std::to_string(totalZombies);

    int zombieType = rand() % TYPES_OF_ZOMBIE;

    std::shared_ptr<Zombie> zombiePtr;

    switch (zombieType) {
        case 1:
            zombiePtr = std::make_shared<Infected>(spawnX, spawnY, zombieId);
            break;
        case 2:
            zombiePtr = std::make_shared<Jumper>(spawnX, spawnY, zombieId);
            break;
        case 3:
            zombiePtr = std::make_shared<Witch>(spawnX, spawnY, zombieId);
            break;
        case 4:
            zombiePtr = std::make_shared<Spear>(spawnX, spawnY, zombieId);
            break;
        case 5:
            zombiePtr = std::make_shared<Venom>(spawnX, spawnY, zombieId);
            break;
    }

    spawnInterval = spawnSettings["SPAWN_INTERVAL"];

    return std::static_pointer_cast<Entity>(zombiePtr);
}