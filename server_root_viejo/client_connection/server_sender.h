#ifndef SERVER_SENDER_H_
#define SERVER_SENDER_H_

#include "thread.h"
#include "socket.h"
#include "../server/server_protocol.h"
#include "action.h"
#include <string>
#include <atomic>

class Sender : public Thread {
    private:
        Socket& peer;
        std::atomic<bool>& is_dead;
        bool& was_closed;
        Server_protocol& protocol;
        Queue<std::shared_ptr<gameStateDTO_t>>* qClient;

    public:
        Sender(Socket &peer,
                bool &was_closed, 
                Server_protocol& protocol, 
                Queue<std::shared_ptr<gameStateDTO_t>>* qClient, 
                std::atomic<bool>& is_dead);

        virtual void run() override;
};

#endif