#include "action_start_shoot.h"

std::vector<int8_t> StartShoot::serialize() const {
    std::vector<int8_t> data = {START_SHOOT};
    return data;
};

bool StartShoot::isExit(void) const {
    return false;
}
