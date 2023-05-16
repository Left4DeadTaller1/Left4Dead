#include "client_sender.h"

ClientSender::ClientSender(Socket skt /*, Match *match*/) : skt(skt), alive(false) /*, match(match)*/ {}

void ClientSender::menu() {}

bool ClientSender::isAlive() { return alive; }

void ClientSender::run() {
    alive = true;
    // menu()
    // ingame()
    bool was_closed = false;
    try {
        while (!was_closed) {
            // match.pop
            // protocol.send
        }
        alive = false;
    } catch (const std::exception &err) {
        std::cerr << "Unexpected exception in client_sender.cpp: "
                  << err.what() << "\n";
    } catch (...) {
        std::cerr << "Unexpected exception in client_sender.cpp: <unknown>\n";
    }
}

ClientSender::~ClientSender() {
    // Destructor implementation
}
