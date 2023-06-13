#include <gtest/gtest.h>

#include "server_protocol.h"

TEST(ServerProtocolTest, TestEncodeServerMessage) {
    ServerProtocol protocol;

    // Create mock Player
    std::shared_ptr<Player> player = std::make_shared<Player>(5, 10, "Player1", SMG);
    player->setMovementState(ENTITY_WALKING);
    player->setMovementDirectionX(ENTITY_RIGHT);
    player->takeDamage(20);

    // Create mock Zombie
    std::shared_ptr<Zombie> zombie = std::make_shared<Zombie>(15, 20, "Zombie1", INFECTED);

    // Add entities to a vector
    std::vector<std::shared_ptr<EntityDTO>> entities;
    entities.push_back(player->getDto());
    entities.push_back(zombie->getDto());

    // Encode the message
    std::shared_ptr<std::vector<uint8_t>> encodedMessagePtr = protocol.encodeServerMessage("gameState", entities);
    std::vector<uint8_t>& encodedMessage = *encodedMessagePtr;

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
        1,      // facingDirection: FACING_RIGHT
        80,     // Health: 80
        1,      // Entity type: Zombie
        0, 1,   // ID: Zombie1
        8,      // General State: IDLE
        0, 15,  // X position: 15 (network byte order)
        0, 20,  // Y position: 20 (network byte order)
        0, 1,   // X Direction: ENTITY_RIGHT
        100,    // Health: 100
        0};     // Zombie type: INFECTED

    EXPECT_EQ(encodedMessage, expectedMessage);
}

TEST(ServerProtocolTest, TestExtractId) {
    ServerProtocol protocol;

    // Test case 1: String with digits
    std::string input1 = "Player123";
    std::string expectedOutput1 = "123";
    std::string extractedId1 = protocol.extractId(input1);
    EXPECT_EQ(extractedId1, expectedOutput1);

    std::string input4 = "Zombie154";
    std::string expectedOutput4 = "154";
    std::string extractedId4 = protocol.extractId(input4);
    EXPECT_EQ(extractedId4, expectedOutput4);

    // Test case 2: String without digits
    std::string input2 = "Zombie";
    std::string expectedOutput2 = "";
    std::string extractedId2 = protocol.extractId(input2);
    EXPECT_EQ(extractedId2, expectedOutput2);

    // Test case 3: Empty string
    std::string input3 = "";
    std::string expectedOutput3 = "";
    std::string extractedId3 = protocol.extractId(input3);
    EXPECT_EQ(extractedId3, expectedOutput3);
}

TEST(ServerProtocolTest, TestEncodeJoinMessage) {
    ServerProtocol protocol;

    // Encode the Join Message
    std::shared_ptr<std::vector<uint8_t>> encodedMessage1Ptr = protocol.encodeServerMessage("JoinMsg", "Player1");
    std::vector<uint8_t>& encodedMessage1 = *encodedMessage1Ptr;

    std::shared_ptr<std::vector<uint8_t>> encodedMessage2Ptr = protocol.encodeServerMessage("JoinMsg", "Player4");
    std::vector<uint8_t>& encodedMessage2 = *encodedMessage2Ptr;

    // Check the encoded message
    std::vector<uint8_t> expectedMessage1 = {2, 1};  // Message type JoinMsg with Player ID 1
    std::vector<uint8_t> expectedMessage2 = {2, 4};  // Message type JoinMsg with Player ID 4
    EXPECT_EQ(encodedMessage1, expectedMessage1);
    // TODO ASK FEDE WTF this doesn't work, bc in ForthPlayerJoinsLobby test it works perfectly
    EXPECT_EQ(encodedMessage2, expectedMessage2);
}
