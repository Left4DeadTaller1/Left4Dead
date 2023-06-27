#include "client_connection.h"
#define MY_SHUT_RDWR 2
constexpr size_t QUEUE_SIZE = 16000;

ClientConnection::ClientConnection(Socket &&skt, GamesManager &gamesManager)
    : clientSocket(std::move(skt)),
      keepTalking(true),
      alive(true),
      gamesManager(gamesManager),
      gameResponses(QUEUE_SIZE),
      sender(clientSocket, gameResponses),
      receiver(clientSocket, gamesManager, gameResponses) {}

void ClientConnection::connectToClient() {
    std::cout << "ENTRA A CLIENT CONNECTION\n";
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

bool ClientConnection::isRemovable() {
    return !alive;
}

void ClientConnection::kill() {
    keepTalking = false;
    // Socket follows RAII no need for those
    // clientSocket.shutdown(MY_SHUT_RDWR);
    // clientSocket.close();

    sender.stop();
    receiver.stop();

    // The game closes the queue in the destructor
    //  gameResponses.close();

    sender.join();
    receiver.join();

    alive = false;
}

ClientConnection::~ClientConnection() {
    if (alive) {
        kill();
    }
}
