#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <string>
#include <vector>

#include "../game/server_message.h"
#include "queue.h"
#include "socket.h"
#include "thread.h"

class ClientSender : public Thread {
   private:
    Socket& clientSocket;
    Queue<ServerMessage>& gameResponses;
    bool isRunning;
    // Match match;
    // Protocol protocol;

   public:
    ClientSender(Socket& skt, Queue<ServerMessage>& gameResponses);

    void run() override;

    void menu();  //  TODO: Preguntar a Fede si el menu es monothread

    bool getIsRunning();
    void stop();

    ~ClientSender();
};

#endif  // CLIENT_SENDER_H