#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "common_thread.h"
#include "common_socket.h"
#include "server_games.h"
#include "server_protocol.h"
#include "server_requester.h"
#include <string>
#include <atomic>

class Receiver : public Thread {
    private:
        Socket& peer;
        std::atomic<bool>& is_dead_receiver_;
        Games& games;
        bool& was_closed;
        Server_protocol& protocol;
        Queue<std::string>* queue;
        Game* game;
        Requester requester;

    public:
        Receiver(Socket &peer, Games& games, 
                bool& was_closed, //poner atomico
                Server_protocol& protocol, 
                Queue<std::string>* queue, 
                unsigned int code, 
                std::atomic<bool>& is_dead);

        virtual void run() override;
};

#endif //SERVER_RECEIVER_H_