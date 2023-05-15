#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "dipa_classes/socket.h"
#include "dipa_classes/thread.h"

class Client : public Thread {
   private:
    Socket skt;
    std::atomic<bool> alive;
    // Match match;
    // Protocol protocol;

    // ClientSender sender;

   public:
    Client(Socket skt /*, Match *match*/);

    void run() override;

    void menu();  //  Client is in the Menu

    bool isAlive();

    ~Client();
};

#endif  // CLIENT_CONNECTION_H