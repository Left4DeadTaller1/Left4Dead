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

std::string HiloMensajes::typeMapToString(TypeMap_t typeMap){
    if (typeMap == WAR1_BRIGHT){
        return "War 1 Bright";
    }
    if (typeMap == WAR1_PALE){
        return "War 1 Pale";
    }
    if (typeMap == WAR2_BRIGHT){
        return "War 2 Bright";
    }
    if (typeMap == WAR2_PALE){
        return "War 2 Pale";
    }
    if (typeMap == WAR3_BRIGHT){
        return "War 3 Bright";
    }
    if (typeMap == WAR3_PALE){
        return "War 3 Pale";
    }
    if (typeMap == WAR4_BRIGHT){
        return "War 4 Bright";
    }
    if (typeMap == WAR4_PALE){
        return "War 4 Pale";
    }
    return "";
}

const QString HiloMensajes::encodeInfoGame(TypeMap_t typeMap, int amountPlayers, 
                            std::vector<infoPlayerDTO_t>& infoPlayers){

    std::string infoGame;
    infoGame += typeMapToString(typeMap);
    infoGame += ";";
    infoGame += std::to_string(amountPlayers);
    infoGame += ";";

    for (auto &player : infoPlayers){
        infoGame += player.nickname;
        infoGame += ";";
        infoGame += typeWeaponToString(player.typeWeapon);
        infoGame += ";";
    }

    return QString::fromStdString(infoGame);
}

void HiloMensajes::run() {try {
    bool wasClosed = false;
    int typeMessage = protocol.receiveTypeMessage(wasClosed);
    if (typeMessage == MSG_JOIN){
        std::shared_ptr<infoGameDTO_t> infoGame = protocol.receiveCreateorJoin(wasClosed);
        emit infoGameReceived(encodeInfoGame(infoGame->typeMap, infoGame->amountPlayers, 
                            infoGame->infoPlayers));
    } while (!wasClosed) {
        int typeMessage = protocol.receiveTypeMessage(wasClosed);
        if (typeMessage == MSG_START){
            emit closedWithoutError(0);
            break;
        }
        if (typeMessage == MSG_JOIN){
            std::shared_ptr<infoGameDTO_t> infoGame = protocol.receiveCreateorJoin(wasClosed);

            emit infoGameReceived(encodeInfoGame(infoGame->typeMap, infoGame->amountPlayers, 
                                infoGame->infoPlayers));
        }
    }
    }catch (const std::exception &e) {
        std::cout << "PONER UN BOOL\n";
    }
}

