#include <gtest/gtest.h>

#include "server_protocol.h"

TEST(ServerProtocolTest, TestEncodeDecodeServerMessage) {
    ServerProtocol protocol;
    ServerMessage originalMessage("gameState", "This is a test message");
    std::vector<uint8_t> encodedMessage = protocol.encodeServerMessage(originalMessage);
    ServerMessage decodedMessage = protocol.decodeServerMessage(encodedMessage);
    EXPECT_EQ(originalMessage.getMessageType(), decodedMessage.getMessageType());
    EXPECT_EQ(originalMessage.getMessage(), decodedMessage.getMessage());
}

TEST(ServerProtocolTest, TestEncodeDecodeServerMessageJoinSuccessful) {
    ServerProtocol protocol;
    ServerMessage originalMessage("JoinAnswer", "JoinSuccess");
    std::vector<uint8_t> encodedMessage = protocol.encodeServerMessage(originalMessage);
    ServerMessage decodedMessage = protocol.decodeServerMessage(encodedMessage);
    EXPECT_EQ(originalMessage.getMessageType(), decodedMessage.getMessageType());
    EXPECT_EQ(originalMessage.getMessage(), decodedMessage.getMessage());
}

TEST(ServerProtocolTest, TestEncodeDecodeServerGameState) {
    ServerProtocol protocol;
    std::string gameState = R"(
        {
            "entities": [
                {
                    "type": "player",
                    "id": "Player1",
                    "x": 1,
                    "y": 2,
                    "health": 100,
                    "movementState": 0,
                    "movementDirectionX": 0,
                    "movementDirectionY": 0,
                    "healthState": 0,
                    "weaponState": 0
                },
                {
                    "type": "zombie",
                    "id": "Zombie1",
                    "x": 3,
                    "y": 4,
                    "health": 50,
                    "movementState": 0,
                    "movementDirectionX": 0,
                    "movementDirectionY": 0,
                    "healthState": 0
                }
            ]
        }
    )";
    ServerMessage originalMessage("gameState", gameState);
    std::vector<uint8_t> encodedMessage = protocol.encodeServerMessage(originalMessage);
    ServerMessage decodedMessage = protocol.decodeServerMessage(encodedMessage);
    EXPECT_EQ(originalMessage.getMessageType(), decodedMessage.getMessageType());
    EXPECT_EQ(originalMessage.getMessage(), decodedMessage.getMessage());
}
