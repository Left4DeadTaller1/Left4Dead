#ifndef SERVER_REQUESTER_H_
#define SERVER_REQUESTER_H_

#include "common_thread.h"
#include "common_socket.h"
#include "server_games.h"
#include "server_protocol.h"
#include <string>
#include <atomic>

class Requester : public Thread {
    private:
        Socket& peer;
        std::atomic<bool>& is_dead_requester;
        std::atomic<bool>& was_closed;
        Server_protocol& protocol;
        Queue<std::string>* queue;

    public:
        Requester(Socket &peer,std::atomic<bool>& was_closed, 
        Server_protocol& protocol, Queue<std::string>* queue, 
        std::atomic<bool>& is_dead_requester);

        virtual void run() override;
};

#endif //SERVER_REQUESTER_H_