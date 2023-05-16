#include "client_connection.h"
#define MY_SHUT_RDWR 2

ClientConnection::ClientConnection(Socket &&skt /*, Match *match*/) : skt(std::move(skt)), alive(false) /*, match(match)*/ {}

void ClientConnection::run() {
    // menu();
    // inGame();
    bool was_closed = false;
    try {
        while (!was_closed) {
            // inGame()
        }
        alive = true;
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in ClientConnection_connection_match: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in ClientConnection_connection_match: <unknown>\n";
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
    // keep_talking = false;
    skt.shutdown(MY_SHUT_RDWR);
    skt.close();

    // sender.stop();

    // sender.join();

    alive = false;
}

ClientConnection::~ClientConnection() {
    if (alive) {
        kill();
    }
}
