#include "zombie_spawner.h"

#include <cstdlib>

#include "game_config.h"

#define TYPES_OF_ZOMBIE 5

// TODO set the spawnInterval with config yaml
ZombieSpawner::ZombieSpawner() : spawnInterval(5), totalZombies(0) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameDimensions = config.getGameDimensions();

    int gameWidth = gameDimensions["GAME_WIDTH"];
    int gameHeight = gameDimensions["GAME_HEIGHT"];
    // Left spawners
    SpawnPoint spawnPoint1 = {0, (gameHeight / 3)};
    SpawnPoint spawnPoint2 = {0, (2 * gameHeight / 3)};

    // Right spawners
    SpawnPoint spawnPoint3 = {(gameWidth - 100), (gameHeight / 3)};
    SpawnPoint spawnPoint4 = {(gameWidth - 100), (2 * gameHeight / 3)};

    spawnPoints.push_back(spawnPoint1);
    spawnPoints.push_back(spawnPoint2);
    spawnPoints.push_back(spawnPoint3);
    spawnPoints.push_back(spawnPoint4);
}

std::shared_ptr<Zombie> ZombieSpawner::spawn() {
    if (spawnInterval > 0) {
        spawnInterval -= 1;
        return nullptr;
    }

    int spawnPointToSpawn = rand() % spawnPoints.size();

    int spawnX = spawnPoints[spawnPointToSpawn].x;
    int spawnY = spawnPoints[spawnPointToSpawn].y;

    totalZombies += 1;
    std::string zombieId = "zombie" + std::to_string(totalZombies);

    int zombieType = rand() % TYPES_OF_ZOMBIE;

    std::shared_ptr<Zombie> zombiePtr = std::make_shared<Zombie>(spawnX, spawnY, zombieId, static_cast<ZombieType>(zombieType));
    spawnInterval = 5;
    return zombiePtr;
}
