#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <atomic>
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
    std::atomic<bool> isRunning;
    Queue<std::shared_ptr<std::vector<uint8_t>>> &gameResponses;
    ServerProtocol protocol;
    void resetGame();

   public:
    // TODO: la queue es para recibir los msgs del cliente pero creeeo que con un recv que ya es bloqueante estaria..., pensar bien desp q no se frene el servidor y sobretodo el juego
    ClientReceiver(Socket &clientSocket, GamesManager &gamesManager, Queue<std::shared_ptr<std::vector<uint8_t>>> &gameResponses);
    void handleCreateAction(std::string nickName, int typeWeapon, int typeMap);
    void handleJoinAction(const int code, std::string playerNickname, int weaponType);
    void handleStartMove(int movementType, int directionXType, int directionYType);
    void handleEndMove(int directionXType, int directionYType);
    void handleStartShoot();
    void handleEndShoot();
    void handleRecharge();
    void handleRevive();
    void handlePlayerDisconnection();
    // void handleBroadcastAction(Socket &clientSocket, bool &was_closed);
    virtual void run() override;
    bool getIsRunning();
    bool isGameFinish();

    void stop();

    ~ClientReceiver();
};

#endif  // CLIENT_RECEIVER_H
