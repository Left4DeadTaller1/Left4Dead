#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <atomic>

#include "socket.h"
#include "thread.h"

class ClientSender : public Thread {
   private:
    Socket &skt;
    std::atomic<bool> alive;
    // Match match;
    // Protocol protocol;

   public:
    ClientSender(Socket skt /*, Match *match*/);

    void run() override;

    void menu();  //  TODO: Preguntar a Fede si el menu es monothread

    bool isAlive();

    ~ClientSender();
};

#endif  // CLIENT_SENDER_H