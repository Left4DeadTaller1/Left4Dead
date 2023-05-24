#include <gtest/gtest.h>

#include "game_thread.h"
#define MAX_QUEUE_SIZE 16000

TEST(GameThreadTest, Constructor) {
    GameThread gameThread;
    // Check that there are no player queues initially
    EXPECT_EQ(gameThread._getPlayerQueues().size(), 0);
}

TEST(GameThreadTest, AddPlayer) {
    GameThread gameThread;
    Queue<int> gameResponses(MAX_QUEUE_SIZE);
    EXPECT_EQ(gameThread._getPlayerQueues().size(), 0);
    gameThread.addPlayer(gameResponses);
    EXPECT_EQ(gameThread._getPlayerQueues().size(), 1);
}
