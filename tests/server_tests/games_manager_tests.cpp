#include <gtest/gtest.h>

#include "games_manager.h"

TEST(GamesManagerTest, CreateLobby) {
    GamesManager manager;
    // Get the gameId this should start in 0
    int gameId = manager._getGameId();
    EXPECT_EQ(gameId, 0);

    manager.createLobby();

    gameId = manager._getGameId();
    // Verify the increase of gameId
    EXPECT_EQ(gameId, 1);

    // Get the games map
    const std::unordered_map<int, std::reference_wrapper<Queue<Action>>>& games = manager._getGames();

    // Verify the size of the games map
    EXPECT_EQ(games.size(), static_cast<std::size_t>(1));

    // Verify that the game with gameId=0 exists in the games map
    EXPECT_TRUE(games.find(0) != games.end());

    // Verify that the value associated with the gameId=0 is not nullptr
    EXPECT_TRUE(games.at(0) != nullptr);
}

TEST(GamesManagerTest, JoinLobby) {
    GamesManager manager;
    manager.createLobby();
    unsigned int gameCode = 0;
    std::optional<std::reference_wrapper<Queue<Action>>> joinResult = manager.joinLobby(gameCode);

    // Verify the expected behavior based on the joinResult and the games map
    EXPECT_TRUE(joinResult.has_value());         // Verify that the optional has a value
    EXPECT_TRUE(joinResult.value() != nullptr);  // Verify that the value is not null
}

TEST(GamesManagerTest, JoinNonexistentLobby) {
    GamesManager manager;
    unsigned int gameCode = 4;
    std::optional<std::reference_wrapper<Queue<Action>>> joinResult = manager.joinLobby(gameCode);

    // Verify the expected behavior based on the joinResult and the games map
    EXPECT_FALSE(joinResult.has_value());     // Verify that the optional does not have a value
    EXPECT_TRUE(joinResult == std::nullopt);  // Verify that the optional is null
}
