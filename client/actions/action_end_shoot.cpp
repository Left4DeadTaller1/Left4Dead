#include "action_end_shoot.h"

std::vector<int8_t> EndShoot::serialize() const {
    std::vector<int8_t> data = {END_SHOOT};
    return data;
};

