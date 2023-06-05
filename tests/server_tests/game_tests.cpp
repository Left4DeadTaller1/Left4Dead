#include <gtest/gtest.h>

#include "game.h"
#include "server_message.h"
#define MAX_QUEUE_SIZE 16000

/*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
   -------------------Tests for clientCommunication------------------
   ________________________________________________________________*/
TEST(GameTest, Constructor) {
    Game gameInstance;
    // Check that there are no player queues initially
    EXPECT_EQ(gameInstance._getPlayerQueues().size(), 4);
    // Check that all player queues are null initially
    for (auto queue : gameInstance._getPlayerQueues()) {
        EXPECT_EQ(queue, nullptr);
    }
}

TEST(GameTest, AddPlayer) {
    Game gameInstance;
    Queue<ServerMessage> gameResponses(MAX_QUEUE_SIZE);
    // Check that the first player queue is null
    EXPECT_EQ(gameInstance._getPlayerQueues()[1], nullptr);
    gameInstance.addPlayer(gameResponses);
    // Check that the first player queue is not null after adding player
    EXPECT_NE(gameInstance._getPlayerQueues()[1], nullptr);
}

TEST(GameTest, RemovePlayer) {
    Game gameInstance;
    Queue<ServerMessage> gameResponses1(MAX_QUEUE_SIZE);
    Queue<ServerMessage> gameResponses2(MAX_QUEUE_SIZE);
    gameInstance.addPlayer(gameResponses1);
    gameInstance.addPlayer(gameResponses2);
    // Check that the first two player queues are not null
    EXPECT_NE(gameInstance._getPlayerQueues()[1], nullptr);
    EXPECT_NE(gameInstance._getPlayerQueues()[2], nullptr);

    // Remove a player
    gameInstance.removePlayer(gameResponses1);
    // Check that the first player queue is null after removal
    EXPECT_EQ(gameInstance._getPlayerQueues()[1], nullptr);
    // Check that the second player queue is still not null
    EXPECT_NE(gameInstance._getPlayerQueues()[2], nullptr);
}

TEST(GameTest, StartStopGame) {
    Game gameInstance;

    EXPECT_FALSE(gameInstance.getGameRunning());

    gameInstance.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_TRUE(gameInstance.getGameRunning());

    gameInstance.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_FALSE(gameInstance.getGameRunning());

    gameInstance.join();
}
