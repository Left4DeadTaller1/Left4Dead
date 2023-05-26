#include "client_connection.h"
#define MY_SHUT_RDWR 2
constexpr size_t QUEUE_SIZE = 16000;

ClientConnection::ClientConnection(Socket &&skt, GamesManager &gamesManager)
    : clientSocket(std::move(skt)),
      keepTalking(true),
      alive(true),
      gamesManager(gamesManager),
      gameResponses(QUEUE_SIZE),
      sender(ClientSender(clientSocket, gameResponses)),
      receiver(ClientReceiver(clientSocket, gamesManager, gameResponses)) {}

void ClientConnection::connectoToClient() {
    // Iniciar los hilos sender y receiver
    sender.start();
    receiver.start();
}

void ClientConnection::checkThreads() {
    if (!receiver.getIsRunning() || !sender.getIsRunning()) {
        alive = false;
    }
}

bool ClientConnection::isDead() {
    return !alive;
}

void ClientConnection::kill() {
    keepTalking = false;
    clientSocket.shutdown(MY_SHUT_RDWR);
    clientSocket.close();

    sender.stop();
    receiver.stop();

    gameResponses.close();

    sender.join();
    receiver.join();

    alive = false;
}

ClientConnection::~ClientConnection() {
    if (alive) {
        kill();
    }
}
