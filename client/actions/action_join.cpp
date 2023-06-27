#include "action_join.h"

JoinAction::JoinAction(std::string namePlayer, 
                std::string weaponPlayer, 
                std::string code): namePlayer(namePlayer),
                typeWeapon(P90), code(0) {

    if (weaponPlayer == "P90"){
        typeWeapon = P90;
    }
    if (weaponPlayer == "Rifle"){
        typeWeapon = RIFLE;
    }
    if (weaponPlayer == "Sniper"){
        typeWeapon = SNIPER;
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
