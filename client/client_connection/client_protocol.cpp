#include "client_protocol.h"
#include <arpa/inet.h>
#include <iostream>

#define PLAYER 0
#define INFECTED 1

ClientProtocol::ClientProtocol(const std::string& hostname,const std::string& servname) :
    skt(hostname.c_str(), servname.c_str()){}

void ClientProtocol::sendAction(std::shared_ptr<ActionClient> action, bool& wasClosed){
    std::vector<int8_t> data = action->serialize();
    skt.sendall(&data[0], data.size(), &wasClosed);
}

int ClientProtocol::receiveTypeMessage(bool& wasClosed){
    uint8_t messageType;
    skt.recvall(&messageType, 1, &wasClosed);
    return messageType;
}

std::string traducirType_(int typeInfected){
    if (typeInfected == SOLDIER1){
        return "soldier1";
    }
    if (typeInfected == JUMPER){
        return "jumper";
    }
    if (typeInfected == VENOM){
        return "venom";
    }
    if (typeInfected == WITCH){
        return "witch";
    }
    if (typeInfected == ZOMBIE){
        return "zombie";
    }else {
        return "TIPO NO IDENTIFICADO";
    }
}

std::shared_ptr<gameStateDTO_t> ClientProtocol::receiveStateGame(bool& wasClosed){
    std::vector<player_t> vecPlayers;
    std::vector<infected_t> vecInfected;

    uint16_t amountEntities;
    skt.recvall(&amountEntities, 2, &wasClosed);
    if(wasClosed){
        return NULL;
    }
    amountEntities = ntohs(amountEntities);
    //std::cout << "amount entities: " << amountEntities << "\n";

    for (int i = 0; i < amountEntities; i++){
        uint8_t typeEntity;
        skt.recvall(&typeEntity, 1, &wasClosed);
        if(wasClosed){
            return NULL;
        }

        /*if ((int)typeEntity == INFECTED){
            std::cout << "es un infectado\n";
        } else {
            std::cout << "es un player\n";
        }*/

        uint16_t idEntity;
        skt.recvall(&idEntity, 2, &wasClosed);
        if(wasClosed){
            return NULL;
        }
        idEntity = ntohs(idEntity);

        typeEntity_t typeInfected;
        if ((int)typeEntity == INFECTED){
            uint8_t typeInfected_;
            skt.recvall(&typeInfected_, 1, &wasClosed);
            if(wasClosed){
                return NULL;
            }
            typeInfected = static_cast<typeEntity_t>(typeInfected_);
        }

        std::string nickname;
        uint8_t bullets;
        TypeWeapon_t typeWeapon;
        if ((int)typeEntity == PLAYER){
            uint8_t nickname_len;
            skt.recvall(&nickname_len, 1, &wasClosed);

            char buf_nickname[500];
            skt.recvall(buf_nickname, nickname_len, &wasClosed);
            buf_nickname[nickname_len] = '\0';
            nickname = buf_nickname;

            uint8_t type;
            skt.recvall(&type, 1, &wasClosed);
            if(wasClosed){
                return NULL;
            }
            typeWeapon = static_cast<TypeWeapon_t>(type);

            skt.recvall(&bullets, 1, &wasClosed);
            if(wasClosed){
                return NULL;
            }
        }

        uint8_t state_;
        skt.recvall(&state_, 1, &wasClosed);
        if(wasClosed){
            return NULL;
        }
        state_t state = static_cast<state_t>(state_);

        uint8_t actionCounter;
        skt.recvall(&actionCounter, 1, &wasClosed);
        if(wasClosed){
            return NULL;
        }

        uint16_t x;
        skt.recvall(&x, 2, &wasClosed);
        if(wasClosed){
            return NULL;
        }
        x = ntohs(x);

        uint16_t y;
        skt.recvall(&y, 2, &wasClosed);
        if(wasClosed){
            return NULL;
        }
        y = ntohs(y);

        uint8_t lookingTo;
        skt.recvall(&lookingTo, 1, &wasClosed);
        if(wasClosed){
            return NULL;
        }

        uint16_t health;
        skt.recvall(&health, 2, &wasClosed);
        if(wasClosed){
            return NULL;
        }
        health = ntohs(health);

        if ((int)typeEntity == PLAYER){
            player_t player;

            player.idPlayer = idEntity;
            player.state = state;
            player.nickname = nickname;
            player.bullets = bullets;
            player.typeWeapon = typeWeapon;
            player.actionCounter = actionCounter;
            player.x = x;
            player.y = y;
            player.lookingTo = lookingTo;
            player.health = health;

            vecPlayers.push_back(player);
        }

        if ((int)typeEntity == INFECTED){
            infected_t infected;

            infected.idInfected = idEntity;
            infected.typeInfected = typeInfected;
            infected.state = state;
            infected.actionCounter = actionCounter;
            infected.x = x;
            infected.y = y;
            infected.lookingTo = lookingTo;
            infected.health = health;

            //std::cout << "se entra a guardar infected con id: " << infected.idInfected << "\n";

            vecInfected.push_back(infected);
        }
    }
    std::shared_ptr<gameStateDTO_t> gameStateDTO = std::make_shared<gameStateDTO_t>();
    gameStateDTO->players = vecPlayers;
    gameStateDTO->infected = vecInfected;
    return gameStateDTO;
}

std::shared_ptr<infoGameDTO_t> ClientProtocol::receiveCreateorJoin(bool& wasClosed){
    //std::cout << "EN CLIENT PROTOCOL\n";
    std::shared_ptr<infoGameDTO_t> infoGameDTO = std::make_shared<infoGameDTO_t>();
    std::vector<infoPlayerDTO_t> infoPlayers;

    uint8_t code;
    std::cout << "en el protocolo: \n";
    skt.recvall(&code, 1, &wasClosed);
    if(wasClosed){
        return NULL;
    }
    infoGameDTO->code = code;
    std::cout << "code: " << (int)code << "\n";

    uint8_t type;
    skt.recvall(&type, 1, &wasClosed);
    if(wasClosed){
        return NULL;
    }
    std::cout << "typeMap: " << (int)type << "\n";
    infoGameDTO->typeMap = static_cast<TypeMap_t>(type);
    std::cout << "typeMap: " << (int)(infoGameDTO->typeMap) << "\n";

    uint8_t amountPlayers;
    skt.recvall(&amountPlayers, 1, &wasClosed);
    if(wasClosed){
        return NULL;
    }
    infoGameDTO->amountPlayers = amountPlayers;
    std::cout << "amountPlayers: " << (int)amountPlayers << "\n";

    for (int i = 0; i < amountPlayers; i++){
        infoPlayerDTO_t player;

        uint8_t id;
        skt.recvall(&id, 1, &wasClosed);
        player.id = id;
        std::cout << "id: " << (int)id << "\n";

        uint8_t nickname_len;
        skt.recvall(&nickname_len, 1, &wasClosed);

        char buf_nickname[500];
        skt.recvall(buf_nickname, nickname_len, &wasClosed);
        buf_nickname[nickname_len] = '\0';
        player.nickname = buf_nickname;
        //std::cout << "player.nickname: " << player.nickname << "\n";

        uint8_t typeWeapon;
        skt.recvall(&typeWeapon, 1, &wasClosed);
        player.typeWeapon = static_cast<TypeWeapon_t>(typeWeapon);
        //std::cout << "player.typeWeapon: " << (int)player.typeWeapon << "\n";

        //std::cout << "antes de push back\n";
        infoPlayers.push_back(player);
        //std::cout << "despues de push back\n";
    }

    infoGameDTO->infoPlayers = infoPlayers;

    return infoGameDTO;
}

void ClientProtocol::closeSocket(){
    skt.shutdown(2);
    skt.close();
}


