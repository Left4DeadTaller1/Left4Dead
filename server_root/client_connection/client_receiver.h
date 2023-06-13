#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <iostream>
#include <vector>

#include "../game/games_manager.h"
#include "../game/server_message.h"
#include "action.h"
#include "queue.h"
#include "server_protocol.h"
#include "socket.h"
#include "thread.h"

class ClientReceiver : public Thread {
   private:
    Socket &clientSocket;
    GamesManager &gamesManager;
    std::shared_ptr<Game> game;
    std::string playerId;
    bool isRunning;
    Queue<std::vector<uint8_t>> &gameResponses;
    ServerProtocol protocol;

   public:
    // TODO: la queue es para recibir los msgs del cliente pero creeeo que con un recv que ya es bloqueante estaria..., pensar bien desp q no se frene el servidor y sobretodo el juego
    ClientReceiver(Socket &clientSocket, GamesManager &gamesManager, Queue<std::vector<uint8_t>> &gameResponses);
    void handleCreateAction();
    void handleJoinAction(const int code);
    void handleGameAction();
    void handleStartMove(int movementType, int directionXType, int directionYType);
    void handleEndMove(int directionXType, int directionYType);
    void handleStartShoot();
    void handleEndShoot();
    void handleRecharge();
    // void handleBroadcastAction(Socket &clientSocket, bool &was_closed);
    virtual void run() override;
    bool getIsRunning();
    void stop();
};

#endif  // CLIENT_RECEIVER_H
