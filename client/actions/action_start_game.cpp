#include "action_start_game.h"

std::vector<int8_t> StartGame::serialize() const {
    std::vector<int8_t> data = {START_GAME};
    return data;
};

bool StartGame::isExit(void) const {
    return false;
}