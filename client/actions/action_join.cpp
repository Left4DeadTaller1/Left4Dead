#include "action_join.h"

JoinAction::JoinAction(std::string namePlayer, 
                TypeWeapon_t weaponPlayer, 
                int code): namePlayer(namePlayer),
                typeWeapon(weaponPlayer), code(code) {}

std::vector<int8_t> JoinAction::serialize() const {
    std::vector<int8_t> data;
    data.push_back(JOIN);
    data.push_back(code);
    data.push_back(static_cast<int8_t>(typeWeapon));
    data.push_back(namePlayer.length());
    data.insert(data.end(), namePlayer.begin(), namePlayer.end());
    return data;
};
