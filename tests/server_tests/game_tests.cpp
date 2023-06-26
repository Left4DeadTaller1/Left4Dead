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
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses(MAX_QUEUE_SIZE);
    // Check that the first player queue is null
    EXPECT_EQ(gameInstance._getPlayerQueues()[0], nullptr);
    gameInstance.addPlayer(gameResponses, "amund");
    // Check that the first player queue is not null after adding player
    EXPECT_NE(gameInstance._getPlayerQueues()[0], nullptr);
}

TEST(GameTest, RemovePlayer) {
    Game gameInstance;
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses1(MAX_QUEUE_SIZE);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses2(MAX_QUEUE_SIZE);
    gameInstance.addPlayer(gameResponses1, "amund");
    gameInstance.addPlayer(gameResponses2, "amund");
    // Check that the first two player queues are not null
    EXPECT_NE(gameInstance._getPlayerQueues()[0], nullptr);
    EXPECT_NE(gameInstance._getPlayerQueues()[1], nullptr);

    // Remove a player
    gameInstance.removePlayer(gameResponses1);
    // Check that the first player queue is null after removal
    EXPECT_EQ(gameInstance._getPlayerQueues()[0], nullptr);
    // Check that the second player queue is still not null
    EXPECT_NE(gameInstance._getPlayerQueues()[1], nullptr);
}

TEST(GameTest, StartStopGame) {
    Game gameInstance;

    EXPECT_FALSE(gameInstance.isGameRunning());

    std::thread gameThread(&Game::run, &gameInstance);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_TRUE(gameInstance.isGameRunning());

    gameInstance.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_FALSE(gameInstance.isGameRunning());

    gameThread.join();
}
