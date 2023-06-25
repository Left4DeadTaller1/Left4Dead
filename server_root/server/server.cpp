#include "server.h"

#include <iostream>
#include <string>

#include "acceptor.h"

Server::Server(const char* servname) : svr_socket(servname), acep_th(svr_socket), isAcceptorRunning(false) {}

void Server::run() {
    // Start the Acceptor thread
    acep_th.start();
    isAcceptorRunning = true;

    std::string input;
    while (std::cin >> input) {
        if (input == "q") {
            break;
        }
    }
}

Server::~Server() {
    if (isAcceptorRunning) {
        acep_th.shutdown();
        acep_th.join();
        isAcceptorRunning = false;
    }
}

// entiendo no necesito llamar nada para liberar los recursos de svr_socket ya tiene un destructor que se encarga de cerrar el socket y liberar sus recursos.
