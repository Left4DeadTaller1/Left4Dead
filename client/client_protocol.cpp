#include "client_protocol.h"
#include <arpa/inet.h>
#include <iostream>

ClientProtocol::ClientProtocol(Socket& skt) :
    skt(skt){}

//NO PROBADA
void ClientProtocol::create(CreateDTO_t* dto, bool& was_closed){
    std::string scenario = dto->scenario;

    int8_t id[1];
    id[0] = CREATE;
    skt.sendsome(id , 1, &was_closed);
    if (was_closed)
        return;

    uint16_t scenario_len[1];
    scenario_len[0] = htons((uint16_t)(scenario.length()));
    skt.sendall(scenario_len, 2, &was_closed);
    if (was_closed)
        return;

    char* scenario_name = (char*)scenario.c_str();
    skt.sendall(scenario_name, scenario.length(), &was_closed);
}

//NO PROBADA
void ClientProtocol::join(JoinDTO_t* dto, bool& was_closed){
    int code = dto->code;

    int8_t id[1];
    id[0] = JOIN;
    skt.sendall(id , 1, &was_closed);
    if (was_closed)
        return;

    uint32_t code_[1];
    code_[0] = htonl((uint32_t)code);
    skt.sendall(code_, 4, &was_closed);
    if (was_closed)
        return;
}

//NO PROBADA
void ClientProtocol::startMove(StartMoveDTO_t* dto, bool& was_closed){
    int difx = dto->dirX;
    int dify = dto->dirY;
    //dto->idPlayer;

    int8_t id[1];
    id[0] = START_MOVE;
    skt.sendall(id , 1, &was_closed);
    if(was_closed)
        return;

    uint32_t buf_difx[1];
    buf_difx[0] = difx;
    buf_difx[0] = htonl((uint32_t)buf_difx[0]);
    skt.sendall(buf_difx , 4, &was_closed);
    if(was_closed)
        return;

    uint32_t buf_dify[1];
    buf_dify[0] = dify;
    buf_dify[0] = htonl((uint32_t)buf_dify[0]);
    skt.sendall(buf_dify, 4, &was_closed);
}

//NO PROBADA
void ClientProtocol::endMove(EndMoveDTO_t* dto, bool& was_closed){
    int8_t id[1];
    id[0] = END_MOVE;
    skt.sendall(id , 1, &was_closed);
}

//NO PROBADA
void ClientProtocol::startGame(bool& was_closed){
    int8_t id[1];
    id[0] = START_GAME;
    skt.sendall(id , 1, &was_closed);
}

//NO PROBADA
void ClientProtocol::sendAction(actionDTO* dto, bool& wasClosed){
    if (dto->type == CREATE){
        std::cout << "se entra a mandar create\n";
        create((CreateDTO_t*)(dto->dto), wasClosed);
    }
    if (dto->type == JOIN){
        join((JoinDTO_t*)(dto->dto), wasClosed);
    }
    if (dto->type == START_GAME){
        startGame(wasClosed);
    }
    if (dto->type == START_MOVE){
        startMove((StartMoveDTO_t*)(dto->dto), wasClosed);
    }
    if (dto->type == END_MOVE){
        endMove((EndMoveDTO_t*)(dto->dto), wasClosed);
    }
}

std::vector<int> ClientProtocol::receive_update_move(bool& was_closed){
    std::vector<int> vector;

    uint32_t buf_posx[1];
    skt.recvall(buf_posx, 4, &was_closed);
    vector.push_back(ntohl(buf_posx[0]));

    uint32_t buf_posy[1];
    skt.recvall(buf_posy, 4, &was_closed);
    vector.push_back(ntohl(buf_posy[0]));
    
    return vector;
}

/*int32_t ClientProtocol::receive_int32(bool& was_closed){
    uint32_t buf[1] = {0};
    skt.recvall(buf, 4, &was_closed);
    uint32_t number = ntohl(buf[0]);
    return number;
}

state_t ClientProtocol::receive_int8(bool& was_closed){
    state_t buf[1];
    skt.recvall(buf, 1, &was_closed);
    return buf[0];
}*/

/*std::shared_ptr<gameStateDTO_t> ClientProtocol::receive_update_game(bool& was_closed){
    std::shared_ptr<gameStateDTO_t> gameStateDTO = std::make_shared<gameStateDTO_t>();
    std::shared_ptr<std::vector<std::shared_ptr<entity_t>>> entities = std::make_shared<std::vector<std::shared_ptr<entity_t>>>();
    gameStateDTO->entities = entities;

    int cant_entities = receive_int32(was_closed);
    std::cout << "se reciben: \n";
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
    std::cout << "antes de retornar\n";
    return gameStateDTO;
}*/

bool ClientProtocol::receiveNotificationJoin(bool& was_closed){
    uint8_t param[1] = {0};
    skt.recvsome(param, 1, &was_closed);

    if ((int)param[0] == 0){
        return true;
    }
    return false;
}

uint32_t ClientProtocol::receive_notification_create(bool& was_closed){
    uint32_t buf_code[1] = {0};
    skt.recvall(buf_code, 4, &was_closed);
    uint32_t code = ntohl(buf_code[0]);
    return code;
}


