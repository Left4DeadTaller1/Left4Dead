#include "hiloMensajes.h"

HiloMensajes::HiloMensajes(ClientProtocol& protocol): 
                                protocol(protocol){}

std::string HiloMensajes::typeWeaponToString(TypeWeapon_t type){
    if (type == WEAPON1){
        return "weapon1";
    }
    if (type == WEAPON2){
        return "weapon2";
    }
    if (type == WEAPON3){
        return "weapon3";
    }
    return "";
}

void HiloMensajes::run() {
    bool wasClosed = false;
    while (!wasClosed)
    {
        int typeMessage = protocol.receiveTypeMessage(wasClosed);
        if (typeMessage == MSG_START){
            break;
        }
        if (typeMessage == MSG_JOIN){
            infoPlayerJoin_t player = protocol.receiveJoin(wasClosed);

            QString nickname = QString::fromStdString(player.nickname);
            QString weapon = QString::fromStdString(typeWeaponToString(player.typeWeapon));

            emit joinReceived(nickname, weapon);
        }
    }
    emit closedWithoutError(0);
}

