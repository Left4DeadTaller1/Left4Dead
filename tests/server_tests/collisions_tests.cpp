// #include <gtest/gtest.h>

// #include <climits>

// #include "collision_detector.h"
// #include "entity.h"
// #include "game_config.h"

// // Colision Test Cases

// TEST(CollisionDetectorTest, IsColliding) {
//     CollisionDetector detector;
//     Player e1(10, 20, "e1", SMG);
//     Player e2(15, 25, "e2", SMG);  // Overlapping with e1
//     Player e3(50, 60, "e3", SMG);  // Not overlapping with e1

//     EXPECT_TRUE(detector.isColliding(e1, 0, 0, e2));
//     EXPECT_FALSE(detector.isColliding(e1, 0, 0, e3));
// }

// TEST(CollisionDetectorTest, CheckForCollisionsInCrossConfiguration) {
//     CollisionDetector detector;

//     // Create entities in a cross configuration
//     Player centerEntity(100, 100, "PlayerCenter", SMG);  // Entity in the center
//     Player rightEntity(125, 100, "PlayerRight", SMG);    // Entity to the right (at 25 units)
//     Player leftEntity(65, 100, "PlayerLeft", SMG);       // Entity to the left (at 35 units)
//     Player topEntity(100, 135, "PlayerTop", SMG);        // Entity above (at 35 units)
//     Player bottomEntity(100, 70, "PlayerBottom", SMG);   // Entity below (at 30 units)

//     std::list<std::shared_ptr<Entity>> entities = {
//         std::make_shared<Player>(rightEntity),
//         std::make_shared<Player>(leftEntity),
//         std::make_shared<Player>(topEntity),
//         std::make_shared<Player>(bottomEntity)};

//     // Move to the right by 10 units (should be limited to 5 units)
//     centerEntity.setMovementDirectionX(ENTITY_RIGHT);   // Set direction to the right
//     centerEntity.setMovementDirectionY(ENTITY_NONE_Y);  // No movement on the Y-axis
//     auto [moveRightX, moveRightY] = detector.checkForCollisions(centerEntity, 10, 0, entities);
//     EXPECT_EQ(moveRightX, 5);
//     EXPECT_EQ(moveRightY, 0);

//     // Move to the left by 20 units (should be limited to 15 units)
//     centerEntity.setMovementDirectionX(ENTITY_LEFT);    // Set direction to the left
//     centerEntity.setMovementDirectionY(ENTITY_NONE_Y);  // No movement on the Y-axis
//     auto [moveLeftX, moveLeftY] = detector.checkForCollisions(centerEntity, -20, 0, entities);
//     EXPECT_EQ(moveLeftX, -15);
//     EXPECT_EQ(moveLeftY, 0);

//     // Move up by 30 units (should be limited to 20 units bc height is 15)
//     centerEntity.setMovementDirectionX(ENTITY_NONE_X);  // No movement on the X-axis
//     centerEntity.setMovementDirectionY(ENTITY_UP);      // Set direction upward
//     auto [moveUpX, moveUpY] = detector.checkForCollisions(centerEntity, 0, 30, entities);
//     EXPECT_EQ(moveUpX, 0);
//     EXPECT_EQ(moveUpY, 20);

//     // Move down by 30 units (should be limited to 15 units)
//     centerEntity.setMovementDirectionX(ENTITY_NONE_X);  // No movement on the X-axis
//     centerEntity.setMovementDirectionY(ENTITY_DOWN);    // Set direction downward
//     auto [moveDownX, moveDownY] = detector.checkForCollisions(centerEntity, 0, -30, entities);
//     EXPECT_EQ(moveDownX, 0);
//     EXPECT_EQ(moveDownY, -15);
// }

// // Attacks Test Cases
// TEST(CollisionDetectorTest, GetBeingShotRight) {
//     CollisionDetector detector;
//     Attack bullet(BULLET, 10, 20, RIGHT, 10, 30, INT_MAX);  // Bullet shooting to the right

//     auto e1 = std::make_shared<Infected>(30, 25, "e1", 0);  // On the right path of the bullet
//     auto e2 = std::make_shared<Infected>(10, 25, "e2", 0);  // On the left path of the bullet

//     std::list<std::shared_ptr<Entity>> entities = {e1, e2};

//     auto entitiesBeingShot = detector.shoot(bullet, entities);
//     EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
//     EXPECT_EQ(entitiesBeingShot.front(), e1);
// }

// TEST(CollisionDetectorTest, GetBeingShotLeft) {
//     CollisionDetector detector;
//     Attack bullet(BULLET, 10, 20, LEFT, 10, 30, INT_MAX);  // Bullet shooting to the left

//     auto e1 = std::make_shared<Infected>(30, 25, "e1", 0);  // On the right path of the bullet
//     auto e2 = std::make_shared<Infected>(10, 25, "e2", 0);  // On the left path of the bullet

//     std::list<std::shared_ptr<Entity>> entities = {e1, e2};

//     auto entitiesBeingShot = detector.shoot(bullet, entities);
//     EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(1));
//     EXPECT_EQ(entitiesBeingShot.front(), e2);
// }

// TEST(CollisionDetectorTest, GetBeingShotNoHit) {
//     CollisionDetector detector;
//     Attack bullet(BULLET, 10, 20, RIGHT, 20, 30, INT_MAX);  // Bullet shooting to the right

//     auto e1 = std::make_shared<Infected>(50, 60, "e1", 0);  // Not in the path of the bullet

//     std::list<std::shared_ptr<Entity>> entities = {e1};

//     auto entitiesBeingShot = detector.shoot(bullet, entities);
//     EXPECT_EQ(entitiesBeingShot.size(), static_cast<std::size_t>(0));  // No entities should be hit
// }

// TEST(CollisionDetectorTest, GetBeingAttackedByMelee) {
//     CollisionDetector detector;
//     Attack melee(MELEE, 10, 20, RIGHT, 10, 30, 20);  // Melee attack to the right

//     auto e1 = std::make_shared<Player>(15, 25, "Player1", SMG);  // Within melee range but in the opposite direction
//     auto e2 = std::make_shared<Player>(50, 60, "Player2", SMG);  // Outside melee range
//     auto e3 = std::make_shared<Player>(25, 25, "Player3", SMG);  // Within melee range and in the correct direction

//     std::vector<std::shared_ptr<Player>> players = {e1, e2, e3};

//     auto playerBeingHit = detector.getPlayersInRange(10, melee, players);
//     EXPECT_EQ(playerBeingHit, e3);
// }

// TEST(CollisionDetectorTest, GetBeingAttackedBySpear) {
//     CollisionDetector detector;
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     Attack spear(SPEAR_ATTACK, 10, 20, RIGHT, 10, entityParams["SPEAR_ATTACK_RANGE"]);  // Spear attack to the right

//     auto player1 = std::make_shared<Player>(15, 25, "Player1", SMG);  // Within spear range but in the opposite direction
//     auto player2 = std::make_shared<Player>(50, 60, "Player2", SMG);  // Outside spear range
//     auto player3 = std::make_shared<Player>(25, 25, "Player3", SMG);  // Within spear range and in the correct direction

//     std::vector<std::shared_ptr<Player>> entities = {player1, player2, player3};

//     auto playerBeingHit = detector.getPlayersInRange(15, spear, entities);

//     EXPECT_EQ(playerBeingHit, player3);
// }

// TEST(CollisionDetectorTest, GetBeingAttackedByShortVenom) {
//     CollisionDetector detector;
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     Attack shortVenom(SHORT_VENOM, 10, 20, RIGHT, 10, 30, entityParams["VENOM_SPRAY_COOLDOWN"]);  // Short venom attack to the right

//     auto player1 = std::make_shared<Player>(15, 25, "Player1", SMG);  // Within short venom range but in the opposite direction
//     auto player2 = std::make_shared<Player>(50, 60, "Player2", SMG);  // Outside short venom range
//     auto player3 = std::make_shared<Player>(25, 25, "Player3", SMG);  // Within short venom range and in the correct direction

//     std::vector<std::shared_ptr<Player>> entities = {player1, player2, player3};

//     auto playerBeingHit = detector.getPlayersInRange(15, shortVenom, entities);
//     EXPECT_EQ(playerBeingHit, player3);
// }

// TEST(CollisionDetectorTest, GetBeingAttackedByLongVenom) {
//     CollisionDetector detector;
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     Attack longVenom(LONG_VENOM, 10, 20, RIGHT, 10, 30, entityParams["VENOM_PROYECTILE_RANGE"]);  // Long venom attack to the right

//     auto player1 = std::make_shared<Player>(15, 35, "Player1", SMG);  // Within long venom range but in the opposite direction
//     auto player2 = std::make_shared<Player>(60, 70, "Player2", SMG);  // Outside long venom range
//     auto player3 = std::make_shared<Player>(45, 20, "Player3", SMG);  // Within long venom range and in the correct direction

//     std::vector<std::shared_ptr<Player>> entities = {player1, player2, player3};

//     auto playerBeingHit = detector.getPlayersInRange(30, longVenom, entities);
//     EXPECT_EQ(playerBeingHit, player3);
// }

// // TEST(CollisionDetectorTest, CheckForBoundaryCollisions) {
// //     CollisionDetector detector;
// //     //

// //     Player e1(10, 20, "e1", SMG);

// //     std::list<std::shared_ptr<Entity>> entities;  // No other entities

// //     // Check that initially there is no collision
// //     EXPECT_FALSE(detector.checkForCollisions(e1, 0, 0, entities));

// //     // Check collision with left boundary
// //     EXPECT_TRUE(detector.checkForCollisions(e1, -20, 0, entities));

// //     // Check collision with top boundary
// //     EXPECT_TRUE(detector.checkForCollisions(e1, 0, -30, entities));

// //     // Check collision with right boundary
// //     EXPECT_TRUE(detector.checkForCollisions(e1, 1510, 0, entities));

// //     // Check collision with bottom boundary
// //     EXPECT_TRUE(detector.checkForCollisions(e1, 0, 160, entities));
// // }
