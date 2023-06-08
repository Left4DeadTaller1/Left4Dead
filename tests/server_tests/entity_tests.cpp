#include <gtest/gtest.h>

#include "entity.h"
#include "player.h"
#include "zombie.h"

// Player Test Cases
TEST(PlayerTest, TestPlayerInitialization) {
    Player player(5, 10, 1, 1, "Player1");
    EXPECT_EQ(player.getId(), "Player1");
    EXPECT_EQ(player.getX(), 5);
    EXPECT_EQ(player.getY(), 10);
    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getMovementState(), ENTITY_IDLE);
    EXPECT_EQ(player.getWeaponState(), WEAPON_IDLE);
}

TEST(PlayerTest, TestPlayerTakeDamage) {
    Player player(5, 10, 1, 1, "Player1");
    player.takeDamage(20);
    EXPECT_EQ(player.getHealth(), 80);
}

TEST(PlayerTest, TestPlayerMovement) {
    Player player(5, 10, 1, 1, "Player1");
    player.move(3, 2);
    EXPECT_EQ(player.getX(), 8);
    EXPECT_EQ(player.getY(), 12);
    player.setMovementDirectionX(ENTITY_LEFT);
    EXPECT_EQ(player.getMovementDirectionX(), ENTITY_LEFT);
}

// Zombie Test Cases
TEST(ZombieTest, TestZombieInitialization) {
    Zombie zombie(15, 20, 1, 1, "Zombie1");
    EXPECT_EQ(zombie.getId(), "Zombie1");
    EXPECT_EQ(zombie.getX(), 15);
    EXPECT_EQ(zombie.getY(), 20);
    EXPECT_EQ(zombie.getHealth(), 100);
    EXPECT_EQ(zombie.getMovementState(), ENTITY_IDLE);
}

TEST(ZombieTest, TestZombieTakeDamage) {
    Zombie zombie(15, 20, 1, 1, "Zombie1");
    zombie.takeDamage(40);
    EXPECT_EQ(zombie.getHealth(), 60);
}
