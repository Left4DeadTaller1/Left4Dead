#include "action_join.h"

Join::Join(int8_t code, std::string namePlayer) : code(code), 
                                                    namePlayer(namePlayer){}

std::vector<int8_t> Join::serialize() const {
    std::vector<int8_t> data;
    data.push_back(JOIN);
    data.push_back(code);
    data.push_back(namePlayer.length());
    data.insert(data.end(), namePlayer.begin(), namePlayer.end());
    return data;
};

bool Join::isExit(void) const {
    return false;
}