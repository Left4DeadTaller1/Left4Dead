#include <gtest/gtest.h>

#include "collision_detector.h"
#include "entity.h"
#include "shot.h"

TEST(CollisionDetectorTest, IsColliding) {
    CollisionDetector detector;
    Player e1(10, 20, 30, 30, "e1");
    Player e2(15, 25, 30, 30, "e2");  // Overlapping with e1
    Player e3(50, 60, 30, 30, "e3");  // Not overlapping with e1

    EXPECT_TRUE(detector.isColliding(e1, 0, 0, e2));
    EXPECT_FALSE(detector.isColliding(e1, 0, 0, e3));
}

TEST(CollisionDetectorTest, CheckForCollisions) {
    CollisionDetector detector;
    Player e1(10, 20, 30, 30, "e1");
    Player e2(15, 25, 30, 30, "e2");  // Overlapping with e1
    Player e3(50, 60, 30, 30, "e3");  // Not overlapping with e1

    std::vector<std::shared_ptr<Entity>> entities = {std::make_shared<Player>(e1),
                                                     std::make_shared<Player>(e2),
                                                     std::make_shared<Player>(e3)};

    bool collision1 = detector.checkForCollisions(*entities[0], 0, 0, entities);
    bool collision2 = detector.checkForCollisions(*entities[1], 0, 0, entities);
    bool collision3 = detector.checkForCollisions(*entities[2], 0, 0, entities);

    EXPECT_TRUE(collision1);
    EXPECT_TRUE(collision2);
    EXPECT_FALSE(collision3);
}

TEST(CollisionDetectorTest, GetBeingShotRight) {
    CollisionDetector detector;
    Shot bullet(true, 10, 20, "right", 10, 30);  // Bullet shooting to the right

    Zombie e1(30, 25, 30, 30, "e1");  // On the right path of the bullet
    Zombie e2(10, 25, 30, 30, "e2");  // On the left path of the bullet

    std::vector<Entity*> entities = {&e1, &e2};

    std::vector<Entity*> entitiesBeingShot = detector.getBeingShot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
    EXPECT_EQ(entitiesBeingShot[0], &e1);
}

TEST(CollisionDetectorTest, GetBeingShotLeft) {
    CollisionDetector detector;
    Shot bullet(true, 10, 20, "left", 10, 30);  // Bullet shooting to the left

    Zombie e1(30, 25, 30, 30, "e1");  // On the right path of the bullet
    Zombie e2(10, 25, 30, 30, "e2");  // On the left path of the bullet

    std::vector<Entity*> entities = {&e1, &e2};

    std::vector<Entity*> entitiesBeingShot = detector.getBeingShot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
    EXPECT_EQ(entitiesBeingShot[0], &e2);
}

TEST(CollisionDetectorTest, GetBeingShotNoHit) {
    CollisionDetector detector;
    Shot bullet(true, 10, 20, "right", 10, 30);  // Bullet shooting to the right

    Zombie e1(50, 60, 30, 30, "e1");  // Not in the path of the bullet

    std::vector<Entity*> entities = {&e1};

    std::vector<Entity*> entitiesBeingShot = detector.getBeingShot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(0));  // No entities should be hit
}
