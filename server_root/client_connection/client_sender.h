#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <string>
#include <vector>

#include "queue.h"
#include "socket.h"
#include "thread.h"

class ClientSender : public Thread {
   private:
    Socket &clientSocket;
    Queue<std::vector<uint8_t>> &queue;
    bool isRunning;
    // Match match;
    // Protocol protocol;

   public:
    ClientSender(Socket &skt, Queue<std::vector<uint8_t>> &queue);

    void run() override;

    void menu();  //  TODO: Preguntar a Fede si el menu es monothread

    bool getIsRunning();
    void stop();

    ~ClientSender();
};

#endif  // CLIENT_SENDER_H