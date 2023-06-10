#include "server_protocol.h"
#include <arpa/inet.h>
#include <iostream>

ServerProtocol::ServerProtocol(void) {}

int ServerProtocol::receiveTypeCommand(bool &wasClosed, Socket &peer){
    uint8_t type;
    peer.recvsome(&type, 1, &wasClosed);
    return type;
}

std::string ServerProtocol::receiveCreate(bool &wasClosed, Socket &peer){
    uint8_t scenario_len;
    peer.recvall(&scenario_len, 1, &wasClosed);

    char buf_scenario_name[500];
    peer.recvall(buf_scenario_name, scenario_len, &wasClosed);
    buf_scenario_name[scenario_len] = '\0';

    return buf_scenario_name;
}

uint8_t ServerProtocol::receiveJoin(bool &wasClosed, Socket &peer){
    uint8_t code;
    peer.recvall(&code, 1, &wasClosed);
    return code;
}

std::vector<int> ServerProtocol::receiveStartMove(bool& wasClosed, Socket &peer){
    std::vector<int> vector;

    uint8_t typeMove;
    peer.recvall(&typeMove, 1, &wasClosed);
    vector.push_back(typeMove);

    int8_t x;
    peer.recvall(&x, 1, &wasClosed);
    vector.push_back(x);

    int8_t y;
    peer.recvall(&y, 1, &wasClosed);
    vector.push_back(y);

    //ver si funciona despues
    //peer.recvall(&vector[0], 3, &wasClosed);

    return vector;
}

std::vector<int> ServerProtocol::receiveEndMove(bool& wasClosed, Socket &peer){
    std::vector<int> vector;

    int8_t x;
    peer.recvall(&x, 1, &wasClosed);
    vector.push_back(x);

    int8_t y;
    peer.recvall(&y, 1, &wasClosed);
    vector.push_back(y);

    //ver si funciona despues
    //peer.recvall(&vector[0], 2, &wasClosed);

    return vector;
}

//no se usan:

void ServerProtocol::notifyCreate(uint32_t code, Socket &peer, bool &wasClosed){
    code = htonl(code);
    peer.sendall(&code, 4, &wasClosed);  
}

void ServerProtocol::notifyJoin(uint8_t param, Socket &peer, bool &wasClosed){
    uint8_t id = param;
    peer.sendsome(&id , 1, &wasClosed);
}

