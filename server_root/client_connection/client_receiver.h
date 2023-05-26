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
    // Protocol protocol;
    GamesManager &gamesManager;
    Queue<Action> *gameInputQueue;
    bool isRunning;
    Queue<int> &gameResponses;

   public:
    // TODO: la queue es para recibir los msgs del cliente pero creeeo que con un recv que ya es bloqueante estaria..., pensar bien desp q no se frene el servidor y sobretodo el juego
    ClientReceiver(Socket &clientSocket, GamesManager &gamesManager, Queue<int> &gameResponses);
    void handleCreateAction(Socket &clientSocket, bool &was_closed);
    void handleJoinAction(Socket &clientSocket, bool &was_closed);
    // void handleBroadcastAction(Socket &clientSocket, bool &was_closed);
    virtual void run() override;
    bool getIsRunning();
    void stop();
};

#endif  // CLIENT_RECEIVER_H
