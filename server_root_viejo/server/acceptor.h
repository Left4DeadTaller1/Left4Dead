#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "thread.h"
#include "socket.h"
#include "../client_connection/client_connection.h"
#include "server_protocol.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

class Acceptor : public Thread{
    private:
    Socket skt;
    GameManager& gameManager;
    Server_protocol& protocol;
    std::atomic<bool> stop_;

    public:
    Acceptor(Socket skt, GameManager& gameManager, Server_protocol& protocol);

    virtual void run() override;

    void stop();
};

#endif
