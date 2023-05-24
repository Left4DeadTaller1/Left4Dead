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
    Queue<Action> *gameInputQueue;
    bool isRunning;

   public:
    // TODO: la queue es para recibir los msgs del cliente pero creeeo que con un recv que ya es bloqueante estaria..., pensar bien desp q no se frene el servidor y sobretodo el juego
    ClientReceiver(Socket &skt, Queue<std::vector<uint8_t>> &q, GamesManager &gamesManager);
    void handleCreateAction(Socket &clientSocket, bool &was_closed);
    void handleJoinAction(Socket &clientSocket, bool &was_closed);
    // void handleBroadcastAction(Socket &clientSocket, bool &was_closed);
    virtual void run() override;
    bool getIsRunning();
    void stop();
};

#endif  // CLIENT_RECEIVER_H
