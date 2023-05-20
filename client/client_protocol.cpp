#include "client_protocol.h"
#include <arpa/inet.h>
#include <iostream>

ClientProtocol::ClientProtocol(const std::string& hostname,const std::string& servname) :
    hostname(hostname),
    skt(hostname.c_str(), servname.c_str()){}


void ClientProtocol::create(const std::string& scenario, bool& was_closed){
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

void ClientProtocol::join(int code, bool& was_closed){
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

//NO PROBADA  protocolo.move(difx, dify, was_closed);
void ClientProtocol::move(uint32_t difx, uint32_t dify, bool& was_closed){
    int8_t id[1];
    id[0] = MOVE;
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


std::string ClientProtocol::read(bool& was_closed){
    uint8_t id[1];
    skt.recvall(id, 1, &was_closed);
    if (was_closed){
        return "";
    }

    uint16_t msg_len_[1] = {0};
    skt.recvall(msg_len_, 2, &was_closed);
    uint16_t msg_len = ntohs(msg_len_[0]);
    if (was_closed){
        return "";
    }

    char msg[500];
    skt.recvall(msg, msg_len, &was_closed);
    msg[msg_len] = '\0';

    return msg;
}

bool ClientProtocol::receive_notification_join(bool& was_closed){
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

