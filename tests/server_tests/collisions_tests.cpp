#include <gtest/gtest.h>

#include "collision_detector.h"
#include "entity.h"

// Colision Test Cases

TEST(CollisionDetectorTest, IsColliding) {
    CollisionDetector detector;
    Player e1(10, 20, "e1", SMG);
    Player e2(15, 25, "e2", SMG);  // Overlapping with e1
    Player e3(50, 60, "e3", SMG);  // Not overlapping with e1

    EXPECT_TRUE(detector.isColliding(e1, 0, 0, e2));
    EXPECT_FALSE(detector.isColliding(e1, 0, 0, e3));
}

TEST(CollisionDetectorTest, CheckForCollisions) {
    CollisionDetector detector;
    Player e1(10, 20, "e1", SMG);
    Player e2(15, 25, "e2", SMG);  // Overlapping with e1
    Player e3(50, 60, "e3", SMG);  // Not overlapping with e1

    std::list<std::shared_ptr<Entity>> entities = {std::make_shared<Player>(e1),
                                                   std::make_shared<Player>(e2),
                                                   std::make_shared<Player>(e3)};
    std::list<std::shared_ptr<Entity>> entitiesCopy = entities;

    bool collision1 = detector.checkForCollisions(*entities.front(), 0, 0, entitiesCopy);
    entities.pop_front();
    bool collision2 = detector.checkForCollisions(*entities.front(), 0, 0, entitiesCopy);
    entities.pop_front();
    bool collision3 = detector.checkForCollisions(*entities.front(), 0, 0, entitiesCopy);

    EXPECT_TRUE(collision1);
    EXPECT_TRUE(collision2);
    EXPECT_FALSE(collision3);
}

// Attacks Test Cases
TEST(CollisionDetectorTest, GetBeingShotRight) {
    CollisionDetector detector;
    Attack bullet(BULLET, 10, 20, RIGHT, 10, 30);  // Bullet shooting to the right

    auto e1 = std::make_shared<Infected>(30, 25, "e1", 0);  // On the right path of the bullet
    auto e2 = std::make_shared<Infected>(10, 25, "e2", 0);  // On the left path of the bullet

    std::list<std::shared_ptr<Entity>> entities = {e1, e2};

    auto entitiesBeingShot = detector.shoot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
    EXPECT_EQ(entitiesBeingShot.front(), e1);
}

TEST(CollisionDetectorTest, GetBeingShotLeft) {
    CollisionDetector detector;
    Attack bullet(BULLET, 10, 20, LEFT, 10, 30);  // Bullet shooting to the left

    auto e1 = std::make_shared<Infected>(30, 25, "e1", 0);  // On the right path of the bullet
    auto e2 = std::make_shared<Infected>(10, 25, "e2", 0);  // On the left path of the bullet

    std::list<std::shared_ptr<Entity>> entities = {e1, e2};

    auto entitiesBeingShot = detector.shoot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
    EXPECT_EQ(entitiesBeingShot.front(), e2);
}

TEST(CollisionDetectorTest, GetBeingShotNoHit) {
    CollisionDetector detector;
    Attack bullet(BULLET, 10, 20, RIGHT, 20, 30);  // Bullet shooting to the right

    auto e1 = std::make_shared<Infected>(50, 60, "e1", 0);  // Not in the path of the bullet

    std::list<std::shared_ptr<Entity>> entities = {e1};

    auto entitiesBeingShot = detector.shoot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(0));  // No entities should be hit
}

TEST(CollisionDetectorTest, GetBeingAttackedByMelee) {
    CollisionDetector detector;
    Attack melee(MELEE, 10, 20, RIGHT, 10, 30);  // Melee attack to the right

    auto e1 = std::make_shared<Player>(15, 25, "Player1", SMG);  // Within melee range but in the opposite direction
    auto e2 = std::make_shared<Player>(50, 60, "Player2", SMG);  // Outside melee range
    auto e3 = std::make_shared<Player>(25, 25, "Player3", SMG);  // Within melee range and in the correct direction

    std::vector<std::shared_ptr<Player>> players = {e1, e2, e3};

    auto playerBeingHit = detector.getPlayersInRange(10, melee, players);
    EXPECT_EQ(playerBeingHit, e3);
}

TEST(CollisionDetectorTest, GetBeingAttackedBySpear) {
    CollisionDetector detector;
    Attack spear(SPEAR_ATTACK, 10, 20, RIGHT, 10, 30);  // Spear attack to the right

    auto player1 = std::make_shared<Player>(15, 25, "Player1", SMG);  // Within spear range but in the opposite direction
    auto player2 = std::make_shared<Player>(50, 60, "Player2", SMG);  // Outside spear range
    auto player3 = std::make_shared<Player>(25, 25, "Player3", SMG);  // Within spear range and in the correct direction

    std::vector<std::shared_ptr<Player>> entities = {player1, player2, player3};

    auto playerBeingHit = detector.getPlayersInRange(15, spear, entities);

    EXPECT_EQ(playerBeingHit, player3);
}

TEST(CollisionDetectorTest, GetBeingAttackedByShortVenom) {
    CollisionDetector detector;
    Attack shortVenom(SHORT_VENOM, 10, 20, RIGHT, 10, 30);  // Short venom attack to the right

    auto player1 = std::make_shared<Player>(15, 25, "Player1", SMG);  // Within short venom range but in the opposite direction
    auto player2 = std::make_shared<Player>(50, 60, "Player2", SMG);  // Outside short venom range
    auto player3 = std::make_shared<Player>(25, 25, "Player3", SMG);  // Within short venom range and in the correct direction

    std::vector<std::shared_ptr<Player>> entities = {player1, player2, player3};

    auto playerBeingHit = detector.getPlayersInRange(15, shortVenom, entities);
    EXPECT_EQ(playerBeingHit, player3);
}

TEST(CollisionDetectorTest, GetBeingAttackedByLongVenom) {
    CollisionDetector detector;
    Attack longVenom(LONG_VENOM, 10, 20, RIGHT, 10, 30);  // Long venom attack to the right

    auto player1 = std::make_shared<Player>(15, 35, "Player1", SMG);  // Within long venom range but in the opposite direction
    auto player2 = std::make_shared<Player>(60, 70, "Player2", SMG);  // Outside long venom range
    auto player3 = std::make_shared<Player>(45, 20, "Player3", SMG);  // Within long venom range and in the correct direction

    std::vector<std::shared_ptr<Player>> entities = {player1, player2, player3};

    auto playerBeingHit = detector.getPlayersInRange(30, longVenom, entities);
    EXPECT_EQ(playerBeingHit, player3);
}

TEST(CollisionDetectorTest, CheckForBoundaryCollisions) {
    CollisionDetector detector;
    //

    Player e1(10, 20, "e1", SMG);

    std::list<std::shared_ptr<Entity>> entities;  // No other entities

    // Check that initially there is no collision
    EXPECT_FALSE(detector.checkForCollisions(e1, 0, 0, entities));

    // Check collision with left boundary
    EXPECT_TRUE(detector.checkForCollisions(e1, -20, 0, entities));

    // Check collision with top boundary
    EXPECT_TRUE(detector.checkForCollisions(e1, 0, -30, entities));

    // Check collision with right boundary
    EXPECT_TRUE(detector.checkForCollisions(e1, 1510, 0, entities));

    // Check collision with bottom boundary
    EXPECT_TRUE(detector.checkForCollisions(e1, 0, 160, entities));
}
