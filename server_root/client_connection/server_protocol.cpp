#include "server_protocol.h"

#include <arpa/inet.h>

#include <iostream>

/*ServerProtocol::ServerProtocol(const std::string& servname) :
    servname(servname){}*/

ServerProtocol::ServerProtocol(void) {}

void ServerProtocol::notify_create(uint32_t code, Socket &peer, bool &was_closed) {
    uint32_t buf_code[1];
    buf_code[0] = htonl(code);
    peer.sendall(buf_code, 4, &was_closed);
}

void ServerProtocol::notify_join(uint8_t param, Socket &peer, bool &was_closed) {
    uint8_t id[1];
    id[0] = param;
    peer.sendsome(id, 1, &was_closed);
}

void ServerProtocol::send_update_move(uint32_t posx, uint32_t posy, bool &was_closed, Socket &peer) {
    uint32_t buf_posx[1];
    buf_posx[0] = posx;
    buf_posx[0] = htonl((uint32_t)buf_posx[0]);
    peer.sendall(buf_posx, 4, &was_closed);
    if (was_closed)
        return;

    uint32_t buf_posy[1];
    buf_posy[0] = posy;
    buf_posy[0] = htonl((uint32_t)buf_posy[0]);
    peer.sendall(buf_posy, 4, &was_closed);
}

int ServerProtocol::receive_type_of_command(bool &was_closed, Socket &peer) {
    uint8_t buf[1];
    peer.recvsome(buf, 1, &was_closed);

    return (int)buf[0];
}

std::string ServerProtocol::receive_create(bool &was_closed, Socket &peer) {
    uint16_t buf_scenario_len[1];
    peer.recvall(buf_scenario_len, 2, &was_closed);
    uint16_t scenario_len = ntohs(buf_scenario_len[0]);

    char buf_scenario_name[100];  // despues ver cual es el max, creo que esta def
    peer.recvall(buf_scenario_name, scenario_len, &was_closed);
    buf_scenario_name[scenario_len] = '\0';

    return buf_scenario_name;
}

uint32_t ServerProtocol::receive_join(bool &was_closed, Socket &peer) {
    uint32_t buf_code[1];
    peer.recvall(buf_code, 4, &was_closed);
    uint32_t code = ntohl(buf_code[0]);

    return code;
}

std::vector<int> ServerProtocol::receive_start_move(bool &was_closed, Socket &peer) {
    std::vector<int> vector;

    uint32_t buf_difx[1];
    peer.recvall(buf_difx, 4, &was_closed);
    vector.push_back(ntohl(buf_difx[0]));

    uint32_t buf_dify[1];
    peer.recvall(buf_dify, 4, &was_closed);
    vector.push_back(ntohl(buf_dify[0]));

    return vector;
}

std::vector<uint8_t> ServerProtocol::encodeServerMessage(const ServerMessage &msg) {
    uint8_t messageType;
    const std::string &msgType = msg.getMessageType();
    if (msgType == "gameState") {
        messageType = 1;
    } else if (msgType == "JoinAnswer") {
        messageType = 2;
    } else {
        messageType = 0;
    }

    uint16_t msg_len = static_cast<uint16_t>(msg.getMessage().size());
    std::vector<uint8_t> encodedMsg(1 + 2 + msg_len);

    encodedMsg[0] = messageType;
    encodedMsg[1] = (msg_len >> 8) & 0xFF;  // High byte
    encodedMsg[2] = msg_len & 0xFF;         // Low byte

    const std::string &messageContent = msg.getMessage();
    std::copy(messageContent.begin(), messageContent.end(), encodedMsg.begin() + 3);

    return encodedMsg;
}

ServerMessage ServerProtocol::decodeServerMessage(const std::vector<uint8_t> &encodedMsg) {
    std::string messageType;
    switch (encodedMsg[0]) {
        case 1:
            messageType = "gameState";
            break;
        case 2:
            messageType = "JoinAnswer";
            break;
        default:
            messageType = "unknown";
            break;
    }
    uint16_t msg_len = ntohs(*reinterpret_cast<const uint16_t *>(&encodedMsg[1]));
    std::string msg(encodedMsg.begin() + 3, encodedMsg.begin() + 3 + msg_len);

    return ServerMessage(messageType, msg);
}
