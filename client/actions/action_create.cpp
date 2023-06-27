#include "action_create.h"

CreateAction::CreateAction(std::string namePlayer, 
                std::string weaponPlayer, 
                std::string map) : namePlayer(namePlayer),
                typeWeapon(P90), typeMap(WAR1_BRIGHT) {

    if (weaponPlayer == "P90"){
        typeWeapon = P90;
    }
    if (weaponPlayer == "Rifle"){
        typeWeapon = RIFLE;
    }
    if (weaponPlayer == "Sniper"){
        typeWeapon = SNIPER;
    }
    if (map == "War 1 Bright"){
        typeMap = WAR1_BRIGHT;
    }
    if (map == "War 1 Pale"){
        typeMap = WAR1_PALE;
    }
    if (map == "War 2 Bright"){
        typeMap = WAR2_BRIGHT;
    }
    if (map == "War 2 Pale"){
        typeMap = WAR2_PALE;
    }
    if (map == "War 3 Bright"){
        typeMap = WAR3_BRIGHT;
    }
    if (map == "War 2 Pale"){
        typeMap = WAR3_PALE;
    }
    if (map == "War 4 Bright"){
        typeMap = WAR4_BRIGHT;
    }
    if (map == "War 4 Pale"){
        typeMap = WAR4_PALE;
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
