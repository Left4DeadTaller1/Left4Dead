#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "socket.h"
#include <string>
#include <memory>
#include <vector>
#include "action.h"
#include "game.h"

class Server_protocol {
    private:
    const std::string servname;

    void send_int32(int32_t number, bool& was_closed, Socket &peer);

    void send_int8(int8_t number, bool& was_closed, Socket &peer);

    public:
    explicit Server_protocol(const std::string& servname);

    //ENVIA

    void notify_create(uint32_t code, Socket &peer, bool &was_closed);

    void notify_join(uint8_t param, Socket &peer, bool &was_closed);

    void send_update_move(uint32_t posx, uint32_t posy, bool& was_closed, Socket &peer);

    //RECIBE

    int receive_type_of_command(bool &was_closed, Socket &peer);

    std::string receive_create(bool &was_closed, Socket &peer);

    uint32_t receive_join(bool &was_closed, Socket &peer);

    std::vector<int> receive_start_move(bool& was_closed, Socket &peer);

    void send_update_game(std::shared_ptr<gameStateDTO_t> gameStateDTO, 
                                        bool& was_closed, 
                                        Socket &peer);

    //std::vector<int> receive_move(bool& was_closed, Socket &peer);

    Server_protocol(const Server_protocol&) = delete;
    Server_protocol& operator=(const Server_protocol&) = delete;

    Server_protocol(Server_protocol&&) = default;
    Server_protocol& operator=(Server_protocol&&) = default;
};

#endif