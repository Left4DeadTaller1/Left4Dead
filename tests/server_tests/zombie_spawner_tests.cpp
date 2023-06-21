#include <gtest/gtest.h>

#include <memory>

#include "game_config.h"
#include "zombie_spawner.h"

TEST(ZombieSpawnerTest, CheckZombieSpawn) {
    ZombieSpawner spawner;
    std::shared_ptr<Entity> entity;
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> spawnSettings = config.getSpawnsParams();

    int framesTillSpawn = spawnSettings["SPAWN_INTERVAL"];

    // The first 4 times spawn() is called, it should return nullptr.
    for (int i = 0; i < (framesTillSpawn - 1); i++) {
        entity = spawner.spawn();
        EXPECT_EQ(entity, nullptr);
    }

    // On the 5th call, it should return a zombie entity.
    entity = spawner.spawn();
    ASSERT_NE(entity, nullptr);

    // Ensure the returned entity has expected properties.
    // Note: This assumes the Entity class has getId(), getX(), and getY() methods.
    EXPECT_EQ(entity->getId().substr(0, 6), "zombie");

    int gameWidth = GameConfig::getInstance().getGameDimensions()["GAME_WIDTH"];
    int gameHeight = GameConfig::getInstance().getGameDimensions()["GAME_HEIGHT"];

    EXPECT_GE(entity->getX(), 0);
    EXPECT_LE(entity->getX(), gameWidth - 100);
    EXPECT_GE(entity->getY(), gameHeight / 3);
    EXPECT_LE(entity->getY(), 2 * gameHeight / 3);
}
