#include "client_protocol.h"
#include <arpa/inet.h>
#include <iostream>

#define PLAYER 0
#define INFECTED 1

ClientProtocol::ClientProtocol(Socket& skt) :
    skt(skt){}

void ClientProtocol::sendAction(std::shared_ptr<ActionClient> action, bool& wasClosed){
    std::vector<int8_t> data = action->serialize();
    skt.sendall(&data[0], data.size(), &wasClosed);
}

int ClientProtocol::receiveCreateorJoin(bool& wasClosed){
    uint8_t code;
    skt.recvall(&code, 1, &wasClosed);
    if(wasClosed){
        return -1;
    }
    return code;
}

void ClientProtocol::receiveExit(bool& wasClosed){
    uint8_t code;
    skt.recvall(&code, 1, &wasClosed);
    if(wasClosed){
        return;
    }
}

int ClientProtocol::receiveTypeCommand(bool& wasClosed){
    uint8_t messageType;
    skt.recvall(&messageType, 1, &wasClosed);
    return messageType;
}

std::shared_ptr<gameStateDTO_t> ClientProtocol::receiveStateGame(bool& wasClosed){
    std::map<uint8_t, player_t> mapPlayers;
    std::map<uint8_t, infected_t> mapInfected;

    uint16_t amountEntities;
    skt.recvall(&amountEntities, 2, &wasClosed);
    if(wasClosed){
        return NULL;
    }
    amountEntities = ntohs(amountEntities);

    for (int i = 0; i < amountEntities; i++){
        uint8_t typeEntity;
        skt.recvall(&typeEntity, 1, &wasClosed);
        if(wasClosed){
            return NULL;
        }

        uint16_t idEntity;
        skt.recvall(&idEntity, 2, &wasClosed);
        idEntity = ntohs(idEntity);

        uint8_t state_;
        skt.recvall(&state_, 1, &wasClosed);
        state_t state = static_cast<state_t>(state_);

        uint16_t x;
        skt.recvall(&x, 2, &wasClosed);
        x = ntohs(x);

        uint16_t y;
        skt.recvall(&y, 2, &wasClosed);
        y = ntohs(y);

        uint16_t lookingTo;
        skt.recvall(&lookingTo, 2, &wasClosed);
        lookingTo = ntohs(lookingTo);

        if ((int)typeEntity == PLAYER){
            uint8_t lookingTo2;
            skt.recvall(&lookingTo2, 1, &wasClosed);
        }

        uint8_t health;
        skt.recvall(&health, 1, &wasClosed);

        if ((int)typeEntity == PLAYER){
            player_t player;

            player.idPlayer = idEntity;
            player.state = state;
            player.x = x;
            player.y = y;
            player.lookingTo = lookingTo;
            player.health = health;

            mapPlayers[idEntity] = player;
        }

        if ((int)typeEntity == INFECTED){
            infected_t infected;

            uint8_t typeInfected;
            skt.recvall(&typeInfected, 1, &wasClosed);

            infected.typeInfected = static_cast<typeEntity_t>(typeInfected);
            infected.idInfected = idEntity;
            infected.state = state;
            infected.x = x;
            infected.y = y;
            infected.lookingTo = lookingTo;

            mapInfected[idEntity] = infected;
        }
    }
    std::shared_ptr<gameStateDTO_t> gameStateDTO = std::make_shared<gameStateDTO_t>();
    gameStateDTO->players = mapPlayers;
    gameStateDTO->infected = mapInfected;
    return gameStateDTO;
}
