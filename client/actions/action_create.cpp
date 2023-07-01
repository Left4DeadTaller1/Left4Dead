#include "action_create.h"

CreateAction::CreateAction(std::string namePlayer, 
                TypeWeapon_t weaponPlayer, 
                TypeMap_t map) : namePlayer(namePlayer),
                typeWeapon(weaponPlayer), typeMap(map) {}

std::vector<int8_t> CreateAction::serialize() const {
    std::vector<int8_t> data;
    data.push_back(CREATE);
    data.push_back(static_cast<int8_t>(typeWeapon));
    data.push_back(static_cast<int8_t>(typeMap));
    data.push_back(namePlayer.length());
    data.insert(data.end(), namePlayer.begin(), namePlayer.end());
    return data;
};
