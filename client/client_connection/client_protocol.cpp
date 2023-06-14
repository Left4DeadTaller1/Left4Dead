#include "client_protocol.h"
#include <arpa/inet.h>
#include <iostream>

ClientProtocol::ClientProtocol(Socket& skt) :
    skt(skt){}

void ClientProtocol::sendAction(std::shared_ptr<ActionClient> action, bool& wasClosed){
    std::vector<int8_t> data = action->serialize();
    skt.sendall(&data[0], data.size(), &wasClosed);
}

std::shared_ptr<gameStateDTO_t> ClientProtocol::receiveStateGame(bool& wasClosed){
    uint8_t messageType;
    skt.recvall(&messageType, 1, &wasClosed);
    if(wasClosed){
        return NULL;
    }
    std::cout << "messageType: " << (int)messageType << "\n";

    if (messageType == 2){
        //despues manejar mensaje!!
        uint8_t message;
        skt.recvall(&message, 1, &wasClosed);
        if(wasClosed){
            return NULL;
        }
    }

    if (messageType != 9){
        return NULL;
    }

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
        if ((int)typeEntity == 0){ //es player
            player_t player;

            uint16_t idPlayer;
            skt.recvall(&idPlayer, 2, &wasClosed);
            player.idPlayer = ntohs(idPlayer);

            uint8_t state;
            skt.recvall(&state, 1, &wasClosed);
            player.state = static_cast<state_t>(state);

            uint16_t x;
            skt.recvall(&x, 2, &wasClosed);
            player.x = ntohs(x);

            uint16_t y;
            skt.recvall(&y, 2, &wasClosed);
            player.y = ntohs(y);

            uint16_t lookingTo2;
            skt.recvall(&lookingTo2, 2, &wasClosed);
            //player.lookingTo = ntohs(lookingTo);

            uint8_t lookingTo;
            skt.recvall(&lookingTo, 1, &wasClosed);
            player.lookingTo = lookingTo;

            skt.recvall(&(player.health), 1, &wasClosed);

            mapPlayers[player.idPlayer] = player;
        }
        if ((int)typeEntity == 1){ //es infected
            infected_t infected;

            uint16_t idInfected;
            skt.recvall(&idInfected, 2, &wasClosed);
            infected.idInfected = ntohs(idInfected);

            uint8_t state;
            skt.recvall(&state, 1, &wasClosed);
            infected.state = static_cast<state_t>(state);

            uint16_t x;
            skt.recvall(&x, 2, &wasClosed);
            infected.x = ntohs(x);

            uint16_t y;
            skt.recvall(&y, 2, &wasClosed);
            infected.y = ntohs(y);

            uint16_t lookingTo;
            skt.recvall(&lookingTo, 2, &wasClosed);
            infected.lookingTo = ntohs(lookingTo);

            skt.recvall(&(infected.health), 1, &wasClosed);

            uint8_t typeInfected;
            skt.recvall(&typeInfected, 1, &wasClosed);
            infected.typeInfected = static_cast<typeEntity_t>(typeInfected);

            mapInfected[infected.idInfected] = infected;
        }
    }
    std::shared_ptr<gameStateDTO_t> gameStateDTO = std::make_shared<gameStateDTO_t>();
    gameStateDTO->players = mapPlayers;
    gameStateDTO->infected = mapInfected;
    return gameStateDTO;
}
