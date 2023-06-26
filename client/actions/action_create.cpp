#include "action_create.h"

CreateAction::CreateAction(std::string namePlayer, 
                std::string weaponPlayer, 
                std::string map) : namePlayer(namePlayer),
                typeWeapon(WEAPON1), typeMap(MAP1) {

    if (weaponPlayer == "weapon1"){
        typeWeapon = WEAPON1;
    }
    if (weaponPlayer == "weapon2"){
        typeWeapon = WEAPON2;
    }
    if (weaponPlayer == "weapon3"){
        typeWeapon = WEAPON3;
    }
    if (map == "map1"){
        typeMap = MAP1;
    }
    if (map == "map2"){
        typeMap = MAP2;
    }
    if (map == "map3"){
        typeMap = MAP3;
    }
    if (map == "map4"){
        typeMap = MAP3;
    }

}

std::vector<int8_t> CreateAction::serialize() const {
    std::vector<int8_t> data;
    data.push_back(CREATE);
    data.push_back(static_cast<int8_t>(typeWeapon));
    data.push_back(static_cast<int8_t>(typeMap));
    data.push_back(namePlayer.length());
    data.insert(data.end(), namePlayer.begin(), namePlayer.end());
    return data;
};

bool CreateAction::isExit(void) const {
    return false;
}
