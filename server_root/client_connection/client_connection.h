#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "game/gameManager.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "socket.h"

class ClientConnection {
   private:
    Socket clientSocket;
    bool keepTalking;
    bool alive;
    //Queue<std::vector<uint8_t>> queue;  // to communicate with the threads
    ClientSender sender;
    ClientReceiver receiver;
    GamesManager& gamesManager;
    ServerProtocol& protocol;

    // ClientSender sender;

   public:
    ClientConnection(Socket&& skt, GamesManager& gamesManager, ServerProtocol& protocol);

    void connectoToClient();
    void checkThreads();

    bool isDead();
    void kill();

    ~ClientConnection();
};

#endif  // CLIENT_CONNECTION_H