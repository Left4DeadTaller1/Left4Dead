#include <gtest/gtest.h>

#include "entity.h"
#include "player.h"
#include "weapon.h"
#include "zombie.h"

// Player Test Cases
TEST(PlayerTest, TestPlayerInitialization) {
    Player player(5, 10, 1, 1, "Player1", SMG);
    EXPECT_EQ(player.getId(), "Player1");
    EXPECT_EQ(player.getX(), 5);
    EXPECT_EQ(player.getY(), 10);
    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getMovementState(), ENTITY_IDLE);
    EXPECT_EQ(player.getWeaponState(), WEAPON_IDLE);
}

TEST(PlayerTest, TestPlayerTakeDamage) {
    Player player(5, 10, 1, 1, "Player1", SMG);
    player.takeDamage(20);
    EXPECT_EQ(player.getHealth(), 80);
}

TEST(PlayerTest, TestPlayerMovement) {
    Player player(5, 10, 1, 1, "Player1", SMG);
    player.move(3, 2);
    EXPECT_EQ(player.getX(), 8);
    EXPECT_EQ(player.getY(), 12);
    player.setMovementDirectionX(ENTITY_LEFT);
    EXPECT_EQ(player.getMovementDirectionX(), ENTITY_LEFT);
}

// Zombie Test Cases
TEST(ZombieTest, TestZombieInitialization) {
    Zombie zombie(15, 20, 1, 1, "Zombie1", INFECTED);
    EXPECT_EQ(zombie.getId(), "Zombie1");
    EXPECT_EQ(zombie.getX(), 15);
    EXPECT_EQ(zombie.getY(), 20);
    EXPECT_EQ(zombie.getHealth(), 100);
    EXPECT_EQ(zombie.getMovementState(), ENTITY_IDLE);
    EXPECT_EQ(zombie.getZombieType(), INFECTED);
}

TEST(ZombieTest, TestZombieTakeDamage) {
    Zombie zombie(15, 20, 1, 1, "Zombie1", INFECTED);
    zombie.takeDamage(40);
    EXPECT_EQ(zombie.getHealth(), 60);
}

// Weapon Test Cases
TEST(WeaponTest, TestWeaponShooting) {
    Weapon smg(SMG);

    // Initially, weapon can shoot
    EXPECT_TRUE(smg.canShoot());

    // Simulate shooting
    smg.shoot(10, RIGHT, 5, 10);

    // Simulate decreasing cooldown to 0
    for (int i = 0; i < SMG_COOLDOWN; ++i) {
        smg.decreaseCooldown();
    }

    // Weapon should be able to shoot again
    EXPECT_TRUE(smg.canShoot());

    // Simulate shooting until out of bullets
    int maxShots = SMG_MAX_BULLETS / SMG_BULLETS_SHOT + 1;
    for (int i = 0; i < maxShots; ++i) {
        smg.shoot(10, RIGHT, 5, 10);
        for (int j = 0; j < SMG_COOLDOWN; ++j) {
            smg.decreaseCooldown();
        }
    }

    // Weapon should not be able to shoot
    EXPECT_FALSE(smg.canShoot());
}

TEST(WeaponTest, TestWeaponReloading) {
    Weapon smg(SMG);

    // Simulate shooting until out of bullets
    int maxShots = SMG_MAX_BULLETS / SMG_BULLETS_SHOT + 1;
    for (int i = 0; i < maxShots; ++i) {
        smg.shoot(10, RIGHT, 5, 10);
        for (int j = 0; j < SMG_COOLDOWN; ++j) {
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