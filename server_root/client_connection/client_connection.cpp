#include "client_connection.h"

Client::Client(Socket skt /*, Match *match*/) : skt(skt) /*, match(match)*/ {}

void Client::run() {
    // alive = true;
    // menu();
    // inGame();

    try {
        while (!was_closed) {
            // inGame()
        }
        is_dead_ = true;
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in client_connection_match: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in client_connection_match: <unknown>\n";
    }
}

void Client::menu() {
    try {
        // while (player in menu) {
        // protocol.receiveMenuInput()
        // }
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in client_connection_menu: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in client_connection_menu: <unknown>\n";
    }
}

void Client::inGame() {
    try {
        // while (connected to game) {
        //  protocol.receiveClientAction()
        //}
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in client_connection_game: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in client_connection_game: <unknown>\n";
    }
}
