#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>

#include "games_manager.h"

TEST(GamesManagerTest, CreateLobby) {
    GamesManager manager;
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses(10);

    int nextGameId = manager._getNextGameId();
    EXPECT_EQ(nextGameId, 0);

    GameRecord gameRecord = manager.createLobby(gameResponses);
    nextGameId = manager._getNextGameId();

    EXPECT_EQ(nextGameId, 1);

    const std::unordered_map<int, std::shared_ptr<Game>>& games = manager._getGames();

    EXPECT_EQ(games.size(), 1);

    EXPECT_TRUE(games.find(0) != games.end());

    EXPECT_TRUE(games.at(0) != nullptr);

    EXPECT_EQ(gameRecord.playerId, "Player1");
    EXPECT_EQ(gameRecord.game, games.at(0));
}

TEST(GamesManagerTest, JoinExistingLobby) {
    GamesManager manager;
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses(10);

    GameRecord gameRecord = manager.createLobby(gameResponses);

    GameRecord gameRecordJoin = manager.joinLobby(0, gameResponses);

    EXPECT_EQ(gameRecordJoin.playerId, "Player2");  // Since player1 is the creator of the game
    EXPECT_EQ(gameRecordJoin.game, gameRecord.game);
}

TEST(GamesManagerTest, ForthPlayerJoinsLobby) {
    GamesManager manager;
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses1(10);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses2(10);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses3(10);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses4(10);

    GameRecord gameRecord = manager.createLobby(gameResponses1);

    GameRecord gameRecordJoin2 = manager.joinLobby(0, gameResponses2);
    GameRecord gameRecordJoin3 = manager.joinLobby(0, gameResponses3);
    GameRecord gameRecordJoin4 = manager.joinLobby(0, gameResponses4);

    EXPECT_EQ(gameRecordJoin2.playerId, "Player2");  // Since player1 is the creator of the game
    EXPECT_EQ(gameRecordJoin3.playerId, "Player3");
    EXPECT_EQ(gameRecordJoin4.playerId, "Player4");
    EXPECT_EQ(gameRecordJoin2.game, gameRecord.game);
    EXPECT_EQ(gameRecordJoin3.game, gameRecord.game);
    EXPECT_EQ(gameRecordJoin4.game, gameRecord.game);
}

TEST(GamesManagerTest, FifthPlayerJoinsLobby_PlayerListFull) {
    GamesManager manager;
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses1(10);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses2(10);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses3(10);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses4(10);
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses5(10);

    GameRecord gameRecord = manager.createLobby(gameResponses1);

    GameRecord gameRecordJoin2 = manager.joinLobby(0, gameResponses2);
    GameRecord gameRecordJoin3 = manager.joinLobby(0, gameResponses3);
    GameRecord gameRecordJoin4 = manager.joinLobby(0, gameResponses4);

    // Attempt to add the fifth player
    EXPECT_THROW(manager.joinLobby(0, gameResponses5), std::out_of_range);
}

TEST(GamesManagerTest, JoinNonexistentLobby) {
    GamesManager manager;
    Queue<std::shared_ptr<std::vector<uint8_t>>> gameResponses(10);

    GameRecord gameRecordJoin = manager.joinLobby(0, gameResponses);

    EXPECT_EQ(gameRecordJoin.game, nullptr);
}
