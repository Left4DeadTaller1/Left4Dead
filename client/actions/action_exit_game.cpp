#include "action_exit_game.h"

std::vector<int8_t> Exit::serialize() const {
    std::vector<int8_t> data = {EXIT};
    return data;
};

bool Exit::isExit(void) const {
    return true;
}