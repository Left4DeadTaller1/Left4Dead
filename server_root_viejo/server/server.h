#ifndef SERVER_H
#define SERVER_H

#include "server_protocol.h"
#include "socket.h"
#include "thread.h"
#include "../game/games_manager.h"
#include "acceptor.h"
#include <string>
#include <utility>
#include <vector>
#include <iostream>

#define GAME_COUNTER_START 0

class Server {
    private:
    Server_protocol protocol;
    Socket skt;

    public:
    explicit Server(const std::string& servname);

    void launch_server(void);
};

#endif
