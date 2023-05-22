#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "../game/games_manager.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "socket.h"

class ClientConnection {
   private:
    Socket clientSocket;
    bool keepTalking;
    bool alive;
    GamesManager& gamesManager;

    Queue<std::vector<uint8_t>> queue;  // to communicate with the threads
    ClientSender sender;
    ClientReceiver receiver;

   public:
    ClientConnection(Socket&& skt, GamesManager& gamesManager);

    void connectoToClient();
    void checkThreads();

    void menu();  //  Client is in the Menu
    void inGame();

    bool isDead();
    void kill();

    ~ClientConnection();
};

#endif  // CLIENT_CONNECTION_H
