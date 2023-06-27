#include "action_revive.h"

std::vector<int8_t> Revive::serialize() const {
    std::vector<int8_t> data = {REVIVE};
    return data;
};