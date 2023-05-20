#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "client_receiver.h"
#include "client_sender.h"
#include "socket.h"

class ClientConnection {
   private:
    Socket clientSocket;
    bool keepTalking;
    bool alive;

    Queue<std::vector<uint8_t>> queue;  // to communicate with the threads
    ClientSender sender;
    ClientReceiver receiver;
    //  MatchManager& matchManager; //reference to games Monitor

    // Match match;
    // Protocol protocol;

    // ClientSender sender;

   public:
    ClientConnection(Socket&& skt /*, Match *match*/);

    void connectoToClient();
    void checkThreads();

    void menu();  //  Client is in the Menu
    void inGame();

    bool isDead();
    void kill();

    ~ClientConnection();
};

#endif  // CLIENT_CONNECTION_H