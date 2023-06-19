#include "server.h"
// #define SHUT_RDWR 2

#include <cstring>
#include <iostream>
#include <string>

#include "acceptor.h"

Server::Server(const char* servname) : svr_socket(servname), acep_th(nullptr) {}
void Server::run() {
    try {
        acep_th = std::make_unique<Acceptor>(svr_socket);
        acep_th->start();

        std::string input;
        while (std::cin >> input) {
            if (input == "q") {
                break;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error in server: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in server" << std::endl;
    }
}

Server::~Server() {
    if (acep_th) {
        acep_th->shutdown();
        acep_th->join();
    }
}

// entiendo no necesito llamar nada para liberar los recursos de svr_socket ya tiene un destructor que se encarga de cerrar el socket y liberar sus recursos.
