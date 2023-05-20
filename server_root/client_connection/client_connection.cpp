#include "client_connection.h"
#define MY_SHUT_RDWR 2
constexpr size_t QUEUE_SIZE = 16000;

ClientConnection::ClientConnection(Socket &&skt /*, MatchManager &matchManager*/)
    : clientSocket(std::move(skt)),
      keepTalking(true),
      alive(true),
      queue(QUEUE_SIZE),
      sender(ClientSender(clientSocket, queue)),
      receiver(ClientReceiver(clientSocket, queue /*, matchManager*/))
/*matchManager(matchManager)*/ {}

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

void ClientConnection::menu() {
    try {
        // while (player in menu) {
        // protocol.receiveMenuInput()
        // }
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in ClientConnection_connection_menu: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in ClientConnection_connection_menu: <unknown>\n";
    }
}

void ClientConnection::inGame() {
    try {
        // while (connected to game) {
        //  protocol.receiveClientConnectionAction()
        //}
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in ClientConnection_connection_game: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in ClientConnection_connection_game: <unknown>\n";
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

    queue.close();

    sender.join();
    receiver.join();

    alive = false;
}

ClientConnection::~ClientConnection() {
    if (alive) {
        kill();
    }
}
