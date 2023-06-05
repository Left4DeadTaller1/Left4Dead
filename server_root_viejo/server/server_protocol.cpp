#include "server_protocol.h"
#include <arpa/inet.h>
#include <iostream>

Server_protocol::Server_protocol(const std::string& servname) :
    servname(servname){}


void Server_protocol::notify_create(uint32_t code, Socket &peer, bool &was_closed){
    uint32_t buf_code[1];
    buf_code[0] = htonl(code);
    peer.sendall(buf_code, 4, &was_closed);  
}

void Server_protocol::notify_join(uint8_t param, Socket &peer, bool &was_closed){
    uint8_t id[1];
    id[0] = param;
    peer.sendsome(id , 1, &was_closed);
}

void Server_protocol::send_update_move(uint32_t posx, uint32_t posy, bool& was_closed, Socket &peer){
    uint32_t buf_posx[1];
    buf_posx[0] = posx;
    buf_posx[0] = htonl((uint32_t)buf_posx[0]);
    peer.sendall(buf_posx , 4, &was_closed);
    if(was_closed)
        return;

    uint32_t buf_posy[1];
    buf_posy[0] = posy;
    buf_posy[0] = htonl((uint32_t)buf_posy[0]);
    peer.sendall(buf_posy, 4, &was_closed);
}

int Server_protocol::receive_type_of_command(bool &was_closed, Socket &peer){
    uint8_t buf[1];
    peer.recvsome(buf, 1, &was_closed);

    return (int)buf[0];
}

std::string Server_protocol::receive_create(bool &was_closed, Socket &peer){
    uint16_t buf_scenario_len[1];
    peer.recvall(buf_scenario_len, 2, &was_closed);
    uint16_t scenario_len = ntohs(buf_scenario_len[0]);

    char buf_scenario_name[100]; //despues ver cual es el max, creo que esta def
    peer.recvall(buf_scenario_name, scenario_len, &was_closed);
    buf_scenario_name[scenario_len] = '\0';

    return buf_scenario_name;
}

uint32_t Server_protocol::receive_join(bool &was_closed, Socket &peer){
    uint32_t buf_code[1];
    peer.recvall(buf_code, 4, &was_closed);
    uint32_t code = ntohl(buf_code[0]);

    return code;
}

std::vector<int> Server_protocol::receive_start_move(bool& was_closed, Socket &peer){
    std::vector<int> vector;

    uint32_t buf_difx[1];
    peer.recvall(buf_difx, 4, &was_closed);
    vector.push_back(ntohl(buf_difx[0]));

    uint32_t buf_dify[1];
    peer.recvall(buf_dify, 4, &was_closed);
    vector.push_back(ntohl(buf_dify[0]));

    return vector;
}

/*std::vector<int> Server_protocol::receive_end_move(bool& was_closed, Socket &peer){

}*/

void Server_protocol::send_int8(int8_t number, bool& was_closed, Socket &peer){
    int8_t buf[1];
    buf[0] = number;
    peer.sendall(buf , 1, &was_closed);
}

void Server_protocol::send_int32(int32_t number, bool& was_closed, Socket &peer){
    int32_t buf[1];
    buf[0] = number;
    buf[0] = htonl((int32_t)buf[0]);
    peer.sendall(buf , 4, &was_closed);
}


void Server_protocol::send_update_game(std::shared_ptr<gameStateDTO_t> gameStateDTO, 
                                        bool& was_closed, 
                                        Socket &peer){
    (*(gameStateDTO->entities)).size();
    send_int32((*(gameStateDTO->entities)).size(), was_closed, peer);
    std::cout << "se envian: \n";
    std::cout << "cant etnidadess: " << (*(gameStateDTO->entities)).size() << "\n";
    if(was_closed){
        return;
    }
    for (auto &entity : *(gameStateDTO->entities)){
        //enviar
        std::cout << "idEntity: " << entity->idEntity << "\n";
        std::cout << "entity->state: " << entity->state << "\n";
        std::cout << "entity->x: " << entity->x << "\n";
        std::cout << "entity->y: " << entity->y << "\n";
        std::cout << "entity->health: " << entity->health << "\n";

        send_int32(entity->idEntity, was_closed, peer);
        if(was_closed){
            return;
        }
        send_int8(entity->state, was_closed, peer);
        if(was_closed){
            return;
        }
        send_int32(entity->x, was_closed, peer);
        if(was_closed){
            return;
        }
        send_int32(entity->y, was_closed, peer);
        if(was_closed){
            return;
        }
        send_int32(entity->health, was_closed, peer);
    }
}
