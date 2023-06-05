#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "../game/games_manager.h"
#include "../game/server_message.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "socket.h"

class ClientConnection {
   private:
    Socket clientSocket;
    bool keepTalking;
    bool alive;
    GamesManager& gamesManager;

    Queue<ServerMessage> gameResponses;  // game responses
    ClientSender sender;
    ClientReceiver receiver;

   public:
    ClientConnection(Socket&& skt, GamesManager& gamesManager);

    void connectToClient();
    void checkThreads();

    void menu();  //  Client is in the Menu
    void inGame();

    bool isDead();
    void kill();

    ~ClientConnection();
};

#endif  // CLIENT_CONNECTION_H
