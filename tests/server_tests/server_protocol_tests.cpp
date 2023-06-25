#include <gtest/gtest.h>

#include "game_config.h"
#include "server_protocol.h"

TEST(ServerProtocolTest, TestEncodeServerMessage) {
    ServerProtocol protocol;
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    // Create mock Player
    std::shared_ptr<Player> player = std::make_shared<Player>(5, 10, "Player1", SMG, "amund");
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
        9,                           // Message type gameState (1 byte)
        0, 2,                        // 2 entities  (2 bytes)
        0,                           // Entity type: Player (1 byte)
        0, 1,                        // ID: Player1 (2 bytes)
        5, 'a', 'm', 'u', 'n', 'd',  // Length of "amund" and the characters themselves
        9,                           // General State: HURT since got attacked (1 byte)
        playerActionCooldown,        // Action Counter: 45 since it got hurt (1 byte)
        0, 5,                        // X position: 5 (network byte order) (2 bytes)
        0, 10,                       // Y position: 10 (network byte order) (2 bytes)
        1,                           // facingDirection: FACING_RIGHT (1 byte)
        0, playerHealth,             // Health: 80 (2 byte)
        1,                           // Entity type: Zombie (1 byte)
        0, 15,                       // ID: Zombie1 (2 bytes)
        0,                           // Zombie type: INFECTED (1 byte)
        12,                          // General State: IDLE (1 byte) //till here is okey
        0,                           // Action Counter: 0 since i didn't do anything (1 byte)
        0, 15,                       // X position: 15 (network byte order) (2 bytes)
        0, 20,                       // Y position: 20 (network byte order) (2 bytes)
        1,                           // facingDirection: FACING_RIGHT (1 byte)
        0, zombieHealth};            // Health: 100 (2 byte)

    // For debugging purposes
    // std::cout << "encodMessage: ";
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

TEST(ServerProtocolTest, TestPlayerActionStateEncoding) {
    ServerProtocol protocol;
    std::shared_ptr<Player> player = std::make_shared<Player>(5, 10, "Player1", SMG, "amund");

    // Initially, the player should be in IDLE state
    GeneralState idleState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(idleState, GeneralState::IDLE);

    // Test for Player Walking State
    player->setActionState(PLAYER_WALKING);
    GeneralState walkingState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(walkingState, GeneralState::WALKING);

    // Test for Player Running State
    player->setActionState(PLAYER_RUNNING);
    GeneralState runningState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(runningState, GeneralState::RUNNING);

    // Test for Player Shooting State
    player->setActionState(PLAYER_SHOOTING);
    GeneralState shootingState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(shootingState, GeneralState::SHOOTING);

    // Test for Player Reloading State
    player->setActionState(PLAYER_RELOADING);
    GeneralState reloadingState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(reloadingState, GeneralState::RELOADING);

    // Test for Player Attacking State
    player->setActionState(PLAYER_ATTACKING);
    GeneralState attackingState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(attackingState, GeneralState::ATTACKING);

    // Test for Player Hurt State
    player->setActionState(PLAYER_HURT);
    GeneralState hurtState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(hurtState, GeneralState::HURT);

    // Test for Player Dying State
    player->setActionState(PLAYER_DYING);
    GeneralState dyingState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(dyingState, GeneralState::DYING);

    // Test for Player Dead State
    player->setActionState(PLAYER_DEAD);
    GeneralState deadState = protocol.determinePlayerState(std::static_pointer_cast<PlayerDTO>(player->getDto()));
    EXPECT_EQ(deadState, GeneralState::DEAD);
}

TEST(ServerProtocolTest, TestWitchActionStateEncoding) {
    ServerProtocol protocol;
    std::shared_ptr<Witch> witch = std::make_shared<Witch>(5, 10, "WitchID", 1);  // Use proper constructor for Witch class.

    // Test for Witch Idle State
    witch->setActionState(WITCH_IDLE);
    GeneralState idleState = protocol.determineWitchState(std::static_pointer_cast<WitchDTO>(witch->getDto()));
    EXPECT_EQ(idleState, GeneralState::IDLE);

    // Test for Witch Moving State
    witch->setActionState(WITCH_MOVING);
    GeneralState movingState = protocol.determineWitchState(std::static_pointer_cast<WitchDTO>(witch->getDto()));
    EXPECT_EQ(movingState, GeneralState::WALKING);  // Use WALKING instead of MOVING

    // Test for Witch Hurt State
    witch->setActionState(WITCH_HURT);
    GeneralState hurtState = protocol.determineWitchState(std::static_pointer_cast<WitchDTO>(witch->getDto()));
    EXPECT_EQ(hurtState, GeneralState::HURT);

    // Test for Witch Dying State
    witch->setActionState(WITCH_DYING);
    GeneralState dyingState = protocol.determineWitchState(std::static_pointer_cast<WitchDTO>(witch->getDto()));
    EXPECT_EQ(dyingState, GeneralState::DYING);

    // Test for Witch Dead State
    witch->setActionState(WITCH_DEAD);
    GeneralState deadState = protocol.determineWitchState(std::static_pointer_cast<WitchDTO>(witch->getDto()));
    EXPECT_EQ(deadState, GeneralState::DEAD);

    // Test for Witch Attacking State
    witch->setActionState(WITCH_ATTACKING);
    GeneralState attackingState = protocol.determineWitchState(std::static_pointer_cast<WitchDTO>(witch->getDto()));
    EXPECT_EQ(attackingState, GeneralState::ATTACKING);

    // Test for Witch Shouting State
    witch->setActionState(WITCH_SHOUTING);
    GeneralState shoutingState = protocol.determineWitchState(std::static_pointer_cast<WitchDTO>(witch->getDto()));
    EXPECT_EQ(shoutingState, GeneralState::SCREAMING);  // Use SCREAMING as a substitute for SHOUTING
}
