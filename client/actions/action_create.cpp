#include "action_create.h"

Create::Create(std::string namePlayer) : namePlayer(namePlayer) {}

std::vector<int8_t> Create::serialize() const {
    std::vector<int8_t> data;
    data.push_back(CREATE);
    data.push_back(namePlayer.length());
    data.insert(data.end(), namePlayer.begin(), namePlayer.end());
    return data;
};

bool Create::isExit(void) const {
    return false;
}
