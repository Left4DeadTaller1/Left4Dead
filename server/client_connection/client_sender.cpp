#include "client_sender.h"

Client::Client(Socket skt /*, Match *match*/) : skt(skt) /*, match(match)*/ {}

void Client::menu();

bool Client::isAlive() { return alive; }

void Client::run() {
    // menu()
    // ingame()
    try {
        while (!was_closed) {
            // match.pop
            // protocol.send
        }
        is_dead_ = true;
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in client_sender.cpp: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in client_sender.cpp: <unknown>\n";
    }
}

~Client();
