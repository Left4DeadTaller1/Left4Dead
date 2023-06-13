#include "zombie_spawner.h"

#include <cstdlib>

#include "game_config.h"

// TODO set the spawnInterval with config yaml
ZombieSpawner::ZombieSpawner() : spawnInterval(100), frameCounter(0) {
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

void ZombieSpawner::update() {
    frameCounter++;
    if (frameCounter >= spawnInterval) {
        frameCounter = 0;
        spawn();
    }
}

void ZombieSpawner::spawn() {
    // int spawnPointToSpawn = rand() % spawnPoints.size();

    // TODO use prototype pattern
}