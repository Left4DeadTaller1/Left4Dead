#include <gtest/gtest.h>

#include "server_protocol.h"

TEST(ServerProtocolTest, TestEncodeServerMessage) {
    ServerProtocol protocol;

    // Create mock Player
    std::shared_ptr<Player> player = std::make_shared<Player>(5, 10, 1, 1, "Player1", SMG);
    player->setMovementState(ENTITY_WALKING);
    player->setMovementDirectionX(ENTITY_RIGHT);
    player->takeDamage(20);

    // Create mock Zombie
    std::shared_ptr<Zombie> zombie = std::make_shared<Zombie>(15, 20, 1, 1, "Zombie1", INFECTED);

    // Add entities to a vector
    std::vector<std::shared_ptr<EntityDTO>> entities;
    entities.push_back(player->getDto());
    entities.push_back(zombie->getDto());

    // Encode the message
    std::vector<uint8_t> encodedMessage = protocol.encodeServerMessage("gameState", entities);

    // Check the encoded message
    std::vector<uint8_t> expectedMessage = {
        1,      // Message type gameState
        0, 2,   // 2 entities
        0,      // Entity type: Player
        0, 1,   // ID: Player1
        0,      // General State: WALKING
        0, 5,   // X position: 5 (network byte order)
        0, 10,  // Y position: 10 (network byte order)
        0, 1,   // X Direction: ENTITY_RIGHT
        80,     // Health: 80
        1,      // Entity type: Zombie
        0, 1,   // ID: Zombie1
        8,      // General State: IDLE
        0, 15,  // X position: 15 (network byte order)
        0, 20,  // Y position: 20 (network byte order)
        0, 1,   // X Direction: ENTITY_RIGHT
        100     // Health: 100
    };

    EXPECT_EQ(encodedMessage, expectedMessage);
}

// TEST(ServerProtocolTest, TestEncodeDecodeServerMessageJoinSuccessful) {
//     ServerProtocol protocol;
//     ServerMessage originalMessage("JoinAnswer", "JoinSuccess");
//     std::vector<uint8_t> encodedMessage = protocol.encodeServerMessage(originalMessage);
//     ServerMessage decodedMessage = protocol.decodeServerMessage(encodedMessage);
//     EXPECT_EQ(originalMessage.getMessageType(), decodedMessage.getMessageType());
//     EXPECT_EQ(originalMessage.getMessage(), decodedMessage.getMessage());
// }

// TEST(ServerProtocolTest, TestEncodeDecodeServerGameState) {
//     ServerProtocol protocol;
//     std::string gameState = R"(
//         {
//             "entities": [
//                 {
//                     "type": "player",
//                     "id": "Player1",
//                     "x": 1,
//                     "y": 2,
//                     "health": 100,
//                     "movementState": 0,
//                     "movementDirectionX": 0,
//                     "movementDirectionY": 0,
//                     "healthState": 0,
//                     "weaponState": 0
//                 },
//                 {
//                     "type": "zombie",
//                     "id": "Zombie1",
//                     "x": 3,
//                     "y": 4,
//                     "health": 50,
//                     "movementState": 0,
//                     "movementDirectionX": 0,
//                     "movementDirectionY": 0,
//                     "healthState": 0
//                 }
//             ]
//         }
//     )";
//     ServerMessage originalMessage("gameState", gameState);
//     std::vector<uint8_t> encodedMessage = protocol.encodeServerMessage(originalMessage);
//     ServerMessage decodedMessage = protocol.decodeServerMessage(encodedMessage);
//     EXPECT_EQ(originalMessage.getMessageType(), decodedMessage.getMessageType());
//     EXPECT_EQ(originalMessage.getMessage(), decodedMessage.getMessage());
// }
