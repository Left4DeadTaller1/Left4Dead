#include <gtest/gtest.h>

#include "entity.h"
#include "game_config.h"
#include "infected.h"
#include "jumper.h"
#include "player.h"
#include "spear.h"
#include "venom.h"
#include "weapon.h"
#include "witch.h"
#include "zombie.h"

// Entity Test Cases
TEST(EntityTest, TestTakingDamage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    Player player(5, 10, "Player1", SMG);
    Infected zombie(15, 20, "Zombie1");
    zombie.takeDamage(20);
    player.takeDamage(20);
    EXPECT_EQ(player.getHealth(), entityParams["PLAYER_HEALTH"] - 20);
    EXPECT_EQ(zombie.getHealth(), entityParams["INFECTED_HEALTH"] - 20);
}

// Player Test Cases
TEST(PlayerTest, TestPlayerInitialization) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    Player player(5, 10, "Player1", SMG);
    EXPECT_EQ(player.getId(), "Player1");
    EXPECT_EQ(player.getX(), 5);
    EXPECT_EQ(player.getY(), 10);
    EXPECT_EQ(player.getHealth(), entityParams["PLAYER_HEALTH"]);
    EXPECT_EQ(player.getMovementState(), ENTITY_IDLE);
    EXPECT_EQ(player.getWeaponState(), WEAPON_IDLE);
    EXPECT_EQ(player.getMovementSpeed(), entityParams["PLAYER_SPEED"]);
}

TEST(PlayerTest, TestPlayerTakeDamage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    Player player(5, 10, "Player1", SMG);
    player.takeDamage(20);
    EXPECT_EQ(player.getHealth(), entityParams["PLAYER_HEALTH"] - 20);
}

TEST(PlayerTest, TestPlayerMovement) {
    Player player(5, 10, "Player1", SMG);
    player.move(3, 2);
    EXPECT_EQ(player.getX(), 8);
    EXPECT_EQ(player.getY(), 12);
    player.setMovementDirectionX(ENTITY_LEFT);
    EXPECT_EQ(player.getMovementDirectionX(), ENTITY_LEFT);
}

// Zombie Test Cases
TEST(ZombieTest, TestZombieInitialization) {
    Infected zombie(15, 20, "Zombie1");
    EXPECT_EQ(zombie.getId(), "Zombie1");
    EXPECT_EQ(zombie.getX(), 15);
    EXPECT_EQ(zombie.getY(), 20);
    EXPECT_EQ(zombie.getHealth(), 100);
    EXPECT_EQ(zombie.getMovementState(), ENTITY_IDLE);
}

TEST(ZombieTest, TestZombieTakeDamage) {
    Infected zombie(15, 20, "Zombie1");
    zombie.takeDamage(40);
    EXPECT_EQ(zombie.getHealth(), 60);
}

TEST(ZombieTest, TestZombieDecideTarget) {
    Infected zombie(10, 10, "Zombie1");

    auto player1 = std::make_shared<Player>(5, 5, "Player1", SMG);
    auto player2 = std::make_shared<Player>(20, 20, "Player2", SMG);
    auto player3 = std::make_shared<Player>(15, 5, "Player3", SMG);

    std::vector<std::shared_ptr<Player>> players = {player1, player2, player3};

    zombie.decideTarget(players);
    // Player1 is the closest to the Zombie. Zombie should move to the bottom left.
    EXPECT_EQ(zombie.getMovementDirectionX(), ENTITY_LEFT);
    EXPECT_EQ(zombie.getMovementDirectionY(), ENTITY_DOWN);
    EXPECT_EQ(zombie.getMovementState(), ENTITY_RUNNING);
}

// // Weapon Test Cases
TEST(WeaponTest, TestWeaponShooting) {
    Weapon smg(SMG);

    // Get game configuration
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> weaponsParams = config.getWeaponsParams();

    int smgCooldown = weaponsParams["SMG_COOLDOWN"];
    int smgMaxBullets = weaponsParams["SMG_MAX_BULLETS"];
    int smgBulletsShot = weaponsParams["SMG_BULLETS_SHOT"];

    // Initially, weapon can shoot
    EXPECT_TRUE(smg.canShoot());

    // Simulate shooting
    smg.shoot(10, RIGHT, 5, 10);

    // Simulate decreasing cooldown to 0
    for (int i = 0; i < smgCooldown; ++i) {
        smg.decreaseCooldown();
    }

    // Weapon should be able to shoot again
    EXPECT_TRUE(smg.canShoot());

    // Simulate shooting until out of bullets
    int maxShots = smgMaxBullets / smgBulletsShot + 1;
    for (int i = 0; i < maxShots; ++i) {
        smg.shoot(10, RIGHT, 5, 10);
        for (int j = 0; j < smgCooldown; ++j) {
            smg.decreaseCooldown();
        }
    }

    // Weapon should not be able to shoot
    EXPECT_FALSE(smg.canShoot());
}

TEST(WeaponTest, TestWeaponReloading) {
    Weapon smg(SMG);

    // Get game configuration
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> weaponsParams = config.getWeaponsParams();

    int smgCooldown = weaponsParams["SMG_COOLDOWN"];
    int smgMaxBullets = weaponsParams["SMG_MAX_BULLETS"];
    int smgBulletsShot = weaponsParams["SMG_BULLETS_SHOT"];

    // Simulate shooting until out of bullets
    int maxShots = smgMaxBullets / smgBulletsShot + 1;
    for (int i = 0; i < maxShots; ++i) {
        smg.shoot(10, RIGHT, 5, 10);
        for (int j = 0; j < smgCooldown; ++j) {
            smg.decreaseCooldown();
        }
    }

    // Weapon should not be able to shoot
    EXPECT_FALSE(smg.canShoot());

    // Reload weapon
    smg.reload();

    // Weapon should be able to shoot
    EXPECT_TRUE(smg.canShoot());
}
