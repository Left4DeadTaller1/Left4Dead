#include "action_recharge.h"

std::vector<int8_t> Recharge::serialize() const {
    std::vector<int8_t> data = {RECHARGE};
    return data;
};

