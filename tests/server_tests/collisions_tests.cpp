#include <gtest/gtest.h>

#include "../../server_root/server/collision_detector.h"
#include "../../server_root/server/entity.h"
#include "../../server_root/server/shot.h"

TEST(CollisionDetectorTest, IsColliding) {
    CollisionDetector detector;
    Entity e1(10, 20, 30, 30);
    Entity e2(15, 25, 30, 30);  // Overlapping with e1
    Entity e3(50, 60, 30, 30);  // Not overlapping with e1

    EXPECT_TRUE(detector.isColliding(e1, e2));
    EXPECT_FALSE(detector.isColliding(e1, e3));
}

TEST(CollisionDetectorTest, GetCollisions) {
    CollisionDetector detector;
    Entity e1(10, 20, 30, 30);
    Entity e2(15, 25, 30, 30);  // Overlapping with e1
    Entity e3(50, 60, 30, 30);  // Not overlapping with e1

    std::vector<Entity *> entities = {&e1, &e2, &e3};
    std::vector<Entity *> collisions = detector.getCollisions(e1, entities);

    EXPECT_EQ(collisions.size(), static_cast<std::size_t>(1));
    EXPECT_EQ(collisions[0], &e2);
}

TEST(CollisionDetectorTest, CheckBeingShotRight) {
    CollisionDetector detector;
    Shot bullet(true, 10, 20, "right", 10, 30);  // Bullet shooting to the right

    Entity e1(30, 25, 30, 30);  // On the right path of the bullet
    Entity e2(10, 25, 30, 30);  // On the left path of the bullet

    std::vector<Entity *> entities = {&e1, &e2};

    std::vector<Entity *> entitiesBeingShot = detector.getBeingShot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
    EXPECT_EQ(entitiesBeingShot[0], &e1);
}

TEST(CollisionDetectorTest, CheckBeingShotLeft) {
    CollisionDetector detector;
    Shot bullet(true, 10, 20, "left", 10, 30);  // Bullet shooting to the left

    Entity e1(30, 25, 30, 30);  // On the right path of the bullet
    Entity e2(10, 25, 30, 30);  // On the left path of the bullet

    std::vector<Entity *> entities = {&e1, &e2};

    std::vector<Entity *> entitiesBeingShot = detector.getBeingShot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
    EXPECT_EQ(entitiesBeingShot[0], &e2);
}

TEST(CollisionDetectorTest, CheckBeingShotNoHit) {
    CollisionDetector detector;
    Shot bullet(true, 10, 20, "right", 10, 30);  // Bullet shooting to the right

    Entity e1(50, 60, 30, 30);  // Not in the path of the bullet

    std::vector<Entity *> entities = {&e1};

    std::vector<Entity *> entitiesBeingShot = detector.getBeingShot(bullet, entities);
    EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(0));  // No entities should be hit
}
