#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <iostream>
#include <vector>

// #include "protocol.h"
#include "../game/games_manager.h"
#include "queue.h"
#include "socket.h"
#include "thread.h"

class ClientReceiver : public Thread {
   private:
    Socket &clientSocket;
    Queue<std::vector<uint8_t>> &queue;
    // Protocol protocol;
    GamesManager &gamesManager;
    bool isRunning;

   public:
    ClientReceiver(Socket &skt, Queue<std::vector<uint8_t>> &q, GamesManager &gamesManager);
    // void handleCreateAction(Socket &clientSocket, bool &was_closed);
    // void handleJoinAction(Socket &clientSocket, bool &was_closed);
    // void handleBroadcastAction(Socket &clientSocket, bool &was_closed);
    virtual void run() override;
    bool getIsRunning();
    void stop();
};

#endif  // CLIENT_RECEIVER_H
