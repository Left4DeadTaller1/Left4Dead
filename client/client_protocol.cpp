#include "client_protocol.h"
#include <arpa/inet.h>
#include <iostream>

ClientProtocol::ClientProtocol(Socket& skt) :
    skt(skt){}

void ClientProtocol::sendAction(std::shared_ptr<ActionClient> action, bool& wasClosed){
    std::vector<int8_t> data = action->serialize();
    skt.sendall(&data[0], data.size(), &wasClosed);
}

int32_t ClientProtocol::receive_int32(bool& was_closed){
    uint32_t buf[1] = {0};
    skt.recvall(buf, 4, &was_closed);
    uint32_t number = ntohl(buf[0]);
    return number;
}

int8_t ClientProtocol::receive_int8(bool& was_closed){
    int8_t buf[1];
    skt.recvall(buf, 1, &was_closed);
    return buf[0];
}

std::shared_ptr<gameStateDTO_t> ClientProtocol::receiveStateGame(bool& was_closed){
    std::shared_ptr<gameStateDTO_t> gameStateDTO = std::make_shared<gameStateDTO_t>();
    std::shared_ptr<std::vector<std::shared_ptr<entity_t>>> entities = std::make_shared<std::vector<std::shared_ptr<entity_t>>>();
    gameStateDTO->entities = entities;

    int cant_entities = receive_int32(was_closed);
    std::cout << "cant entnidades: " << cant_entities << "\n";
    if(was_closed){
        return NULL;
    }
    for (int i = 0; i < cant_entities; i++){
        std::shared_ptr<entity_t> entity = std::make_shared<entity_t>();
        entity->idEntity = receive_int32(was_closed);
        if(was_closed){
            return NULL;
        }
        entity->state = receive_int8(was_closed);
        if(was_closed){
            return NULL;
        }
        entity->x = receive_int32(was_closed);
        if(was_closed){
            return NULL;
        }
        entity->y = receive_int32(was_closed);
        if(was_closed){
            return NULL;
        }
        entity->health = receive_int32(was_closed);

        (gameStateDTO->entities)->push_back(entity);

        std::cout << "idEntity: " << entity->idEntity << "\n";
        std::cout << "entity->state: " << entity->state << "\n";
        std::cout << "entity->x: " << entity->x << "\n";
        std::cout << "entity->y: " << entity->y << "\n";
        std::cout << "entity->health: " << entity->health << "\n"; 
    }
    return gameStateDTO;
}


