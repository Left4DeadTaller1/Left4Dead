#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <string>
#include <vector>

#include "../game/server_message.h"
#include "queue.h"
#include "server_protocol.h"
#include "socket.h"
#include "thread.h"

class ClientSender : public Thread {
   private:
    Socket& clientSocket;
    Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses;
    bool isRunning;
    ServerProtocol protocol;

   public:
    ClientSender(Socket& skt, Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses);

    void run() override;

    void menu();  //  TODO: Preguntar a Fede si el menu es monothread

    bool getIsRunning();
    void stop();

    ~ClientSender();
};

#endif  // CLIENT_SENDER_H