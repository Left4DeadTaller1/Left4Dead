#include "action_join.h"

JoinAction::JoinAction(std::string namePlayer, 
                std::string weaponPlayer, 
                std::string code): namePlayer(namePlayer),
                typeWeapon(WEAPON1), code(0) {

    if (weaponPlayer == "weapon1"){
        typeWeapon = WEAPON1;
    }
    if (weaponPlayer == "weapon2"){
        typeWeapon = WEAPON2;
    }
    if (weaponPlayer == "weapon3"){
        typeWeapon = WEAPON3;
    }
    code = std::stoi(code);
}

std::vector<int8_t> JoinAction::serialize() const {
    std::vector<int8_t> data;
    data.push_back(JOIN);
    data.push_back(code);
    data.push_back(static_cast<int8_t>(typeWeapon));
    data.push_back(namePlayer.length());
    data.insert(data.end(), namePlayer.begin(), namePlayer.end());
    return data;
};

bool JoinAction::isExit(void) const {
    return false;
}