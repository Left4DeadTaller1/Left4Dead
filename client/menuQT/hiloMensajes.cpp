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

const QString HiloMensajes::encodeInfoGame(TypeMap_t typeMap, int amountPlayers, 
                            std::vector<infoPlayerDTO_t>& infoPlayers){

    std::string infoGame;
    infoGame += "Amount players in game: ";
    infoGame += amountPlayers + "\n";

    for (auto &player : infoPlayers){
        infoGame += "Nickname: " + player.nickname + "\n";
        infoGame += "Weapon: " + typeWeaponToString(player.typeWeapon) + "\n";
        infoGame += "---------------------------------------------------------------\n";
    }

    return QString::fromStdString(infoGame);
}

void HiloMensajes::run() {
    //std::cout << "METODO RUN HILO MENSAJES\n";
    bool wasClosed = false;
    int typeMessage = protocol.receiveTypeMessage(wasClosed);
    //std::cout << "typeMessage: " << typeMessage << "\n";
    if (typeMessage == MSG_JOIN){
        //std::cout << "ENTRA A RECIBIR JOIN\n";
        std::shared_ptr<infoGameDTO_t> infoGame = protocol.receiveCreateorJoin(wasClosed);
        /*std::cout << "infoGame->typeMap: " << (int)infoGame->typeMap << "\n";
        std::cout << "infoGame->code: " << (int)infoGame->code << "\n";
        std::cout << "infoGame->amountPlayers: " << (int)infoGame->amountPlayers << "\n";*/
        emit infoGameReceived(encodeInfoGame(infoGame->typeMap, infoGame->amountPlayers, 
                            infoGame->infoPlayers));
    }
    while (!wasClosed)
    {
        int typeMessage = protocol.receiveTypeMessage(wasClosed);
        if (typeMessage == MSG_START){
            break;
        }
        if (typeMessage == MSG_JOIN){
            std::shared_ptr<infoGameDTO_t> infoGame = protocol.receiveCreateorJoin(wasClosed);

            emit infoGameReceived(encodeInfoGame(infoGame->typeMap, infoGame->amountPlayers, 
                                infoGame->infoPlayers));
        }
    }
    emit closedWithoutError(0);
}

