// #include <gtest/gtest.h>

// #include <algorithm>
// #include <iostream>

// #include "games_manager.h"

// TEST(GamesManagerTest, CreateLobby) {
//     GamesManager manager;
//     Queue<ServerMessage> gameResponses(10);

//     // Get the gameId; this should start at 0
//     int gameId = manager._getGameId();
//     EXPECT_EQ(gameId, 0);

//     GameRecord gameRecord = manager.createLobby(gameResponses);
//     gameId = manager._getGameId();

//     // Verify the increase of gameId
//     EXPECT_EQ(gameId, 1);

//     // Get the games map
//     const std::unordered_map<int, std::shared_ptr<Game>>& games = manager._getGames();

//     // Verify the size of the games map
//     EXPECT_EQ(games.size(), 1);

//     // Verify that the game with gameId=0 exists in the games map
//     EXPECT_TRUE(games.find(0) != games.end());

//     // Verify that the value associated with gameId=0 is not nullptr
//     EXPECT_TRUE(games.at(0) != nullptr);

//     // Verify the playerId in the returned GameRecord
//     EXPECT_EQ(gameRecord.playerId, 0);
//     // Verify the game in the returned GameRecord
//     EXPECT_EQ(gameRecord.game, games.at(0));
// }

// TEST(GamesManagerTest, JoinLobby) {
//     GamesManager manager;
//     Queue<ServerMessage> gameResponses;
//     std::string gameId = manager.createLobby();
//     std::string playerId = manager.joinLobby(gameId, gameResponses);
//     EXPECT_EQ(gameResponses.size(), 1);
//     EXPECT_EQ(gameResponses.front().getType(), "JoinLobbyResponse");
//     EXPECT_EQ(gameResponses.front().getMessage(), "Joined lobby");
//     gameResponses.pop();
//     EXPECT_TRUE(manager.isPlayerInLobby(playerId));
// }

// TEST(GamesManagerTest, JoinNonexistentLobby) {
//     GamesManager manager;
//     Queue<ServerMessage> gameResponses;
//     std::string gameCode = "nonexistent";
//     std::string playerId = manager.joinLobby(gameCode, gameResponses);
//     EXPECT_EQ(gameResponses.size(), 1);
//     EXPECT_EQ(gameResponses.front().getType(), "JoinLobbyResponse");
//     EXPECT_EQ(gameResponses.front().getMessage(), "Lobby does not exist");
//     gameResponses.pop();
//     EXPECT_FALSE(manager.isPlayerInLobby(playerId));
// }
