#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_

#include "socket.h"
#include "server_receiver.h"
#include "server_sender.h"
#include "../server/server_protocol.h"
#include "action.h"
#include <atomic>
#include <utility>
#include <string>

//#define TAM_MAX_COLA 1000

class Client_server {
    private:
        Socket peer;
        std::atomic<bool> is_dead_;
        GameManager& gameManager;
        Server_protocol& protocol;
        bool was_closed;
        int idPlayer;
        Receiver receiver;
        Sender sender;
        Queue<std::shared_ptr<gameStateDTO_t>>* qClient;

    public:
        Client_server(Socket peer_, 
                        GameManager& gameManager, 
                        Server_protocol& protocol, 
                        Queue<std::shared_ptr<gameStateDTO_t>>* qClient_);

        void run();

        bool is_dead();

        void stop();

        ~Client_server();
};

#endif  // CLIENT_CONNECTION_H_
