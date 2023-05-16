#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <atomic>

#include "socket.h"
#include "thread.h"

class ClientConnection : public Thread {
   private:
    Socket skt;
    std::atomic<bool> alive;
    // Match match;
    // Protocol protocol;

    // ClientSender sender;

   public:
    bool isDead();
    ClientConnection(Socket&& skt /*, Match *match*/);

    void run() override;

    void menu();  //  Client is in the Menu
    void inGame();

    bool isAlive();
    void kill();

    ~ClientConnection();
};

#endif  // CLIENT_CONNECTION_H