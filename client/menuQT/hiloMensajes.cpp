#include "hiloMensajes.h"

HiloMensajes::HiloMensajes(ClientProtocol& protocol): 
                                protocol(protocol){}

std::string HiloMensajes::typeWeaponToString(TypeWeapon_t type){
    if (type == P90){
        return "P90";
    }
    if (type == RIFLE){
        return "Rifle";
    }
    if (type == SNIPER){
        return "Sniper";
    }
    return "";
}

void HiloMensajes::run() {
    bool wasClosed = false;
    std::shared_ptr<infoGameDTO_t> infoGame = protocol.receiveCreateorJoin(wasClosed);
    emit infoGameReceived(infoGame->typeMap, 
                        infoGame->amountPlayers, 
                        infoGame->infoPlayers);
    while (!wasClosed)
    {
        int typeMessage = protocol.receiveTypeMessage(wasClosed);
        if (typeMessage == MSG_START){
            break;
        }
        if (typeMessage == MSG_JOIN){
            std::shared_ptr<infoGameDTO_t> infoGame = protocol.receiveCreateorJoin(wasClosed);

            emit infoGameReceived(infoGame->typeMap, 
                                infoGame->amountPlayers, 
                                infoGame->infoPlayers);
        }
    }
    emit closedWithoutError(0);
}

