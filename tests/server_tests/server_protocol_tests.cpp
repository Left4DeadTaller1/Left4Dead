#include <gtest/gtest.h>

#include "game_config.h"
#include "server_protocol.h"

TEST(ServerProtocolTest, TestEncodeServerMessage) {
    ServerProtocol protocol;
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    // Create mock Player
    std::shared_ptr<Player> player = std::make_shared<Player>(5, 10, "Player1", SMG);
    player->setMovementDirectionX(ENTITY_RIGHT);
    player->takeDamage(20);
    uint8_t playerHealth = static_cast<uint8_t>(entityParams["PLAYER_HEALTH"] - 20);
    uint8_t playerActionCooldown = static_cast<uint8_t>(entityParams["PLAYER_HURT_DURATION"]);

    // Create mock Zombie
    std::shared_ptr<Infected> zombie = std::make_shared<Infected>(15, 20, "Zombie15", 0);
    uint8_t zombieHealth = static_cast<uint8_t>(entityParams["INFECTED_HEALTH"]);

    // Add entities to a vector
    std::vector<std::shared_ptr<EntityDTO>> entities;
    entities.push_back(player->getDto());
    entities.push_back(zombie->getDto());

    // Encode the message
    std::shared_ptr<std::vector<uint8_t>> encodedMessagePtr = protocol.encodeServerMessage("gameState", entities);
    std::vector<uint8_t>& encodedMessage = *encodedMessagePtr;

    std::vector<uint8_t> expectedMessage = {
        1,                     // Message type gameState (1 byte)
        0, 2,                  // 2 entities  (2 bytes)
        0,                     // Entity type: Player (1 byte)
        0, 1,                  // ID: Player1 (2 bytes)
        9,                     // General State: HURT since got attacked (1 byte)
        playerActionCooldown,  // Action Counter: 45 since it got hurt (1 byte)
        0, 5,                  // X position: 5 (network byte order) (2 bytes)
        0, 10,                 // Y position: 10 (network byte order) (2 bytes)
        1,                     // facingDirection: FACING_RIGHT (1 byte)
        0, playerHealth,       // Health: 80 (2 byte)
        1,                     // Entity type: Zombie (1 byte)
        0, 15,                 // ID: Zombie1 (2 bytes)
        0,                     // Zombie type: INFECTED (1 byte)
        12,                    // General State: IDLE (1 byte) //till here is okey
        0,                     // Action Counter: 0 since i didn't do anything (1 byte)
        0, 15,                 // X position: 15 (network byte order) (2 bytes)
        0, 20,                 // Y position: 20 (network byte order) (2 bytes)
        1,                     // facingDirection: FACING_RIGHT (1 byte)
        0, zombieHealth};      // Health: 100 (2 byte)

    // For debugging purposes
    // std::cout
    //     << "encodMessage: ";
    // for (auto byte : encodedMessage) {
    //     std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "expecMessage: ";
    // for (auto byte : expectedMessage) {
    //     std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    // }
    // std::cout << std::endl;

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
    std::string msgType = "JoinMsg";
    std::string playerId1 = "Player1";
    std::string playerId2 = "Player4";

    // Encode the Join Message
    std::shared_ptr<std::vector<uint8_t>> encodedMessage1Ptr = protocol.encodeServerMessage(msgType, playerId1);
    std::vector<uint8_t>& encodedMessage1 = *encodedMessage1Ptr;

    std::shared_ptr<std::vector<uint8_t>> encodedMessage2Ptr = protocol.encodeServerMessage(msgType, playerId2);
    std::vector<uint8_t>& encodedMessage2 = *encodedMessage2Ptr;

    // Check the encoded message
    std::vector<uint8_t> expectedMessage1 = {2, 1};  // Message type JoinMsg with Player ID 1
    std::vector<uint8_t> expectedMessage2 = {2, 4};  // Message type JoinMsg with Player ID 4
    EXPECT_EQ(encodedMessage1, expectedMessage1);
    // TODO ASK FEDE WTF this doesn't work, bc in ForthPlayerJoinsLobby test it works perfectly
    EXPECT_EQ(encodedMessage2, expectedMessage2);
}
