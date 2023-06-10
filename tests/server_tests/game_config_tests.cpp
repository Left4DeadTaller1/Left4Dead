#include <gtest/gtest.h>

#include "game_config.h"

// GameConfig Test Cases
TEST(GameConfigTest, TestLoadingConfiguration) {
    GameConfig& config = GameConfig::getInstance();

    std::map<std::string, int> gameParams = config.getGameParams();
    EXPECT_EQ(gameParams["SMG_COOLDOWN"], 10);
}
