#include <gtest/gtest.h>

#include "game_config.h"

// GameConfig Test Cases
TEST(GameConfigTest, TestLoadingConfiguration) {
    GameConfig& config = GameConfig::getInstance();

    std::map<std::string, int> weaponsParams = config.getWeaponsParams();
    EXPECT_EQ(weaponsParams["SMG_COOLDOWN"], 10);
}
