#include "server.h"
// #define SHUT_RDWR 2

#include <cstring>
#include <iostream>
#include <string>

#include "acceptor.h"

Server::Server(const char *servname) : svr_socket(servname),
                                        acep_th(svr_socket) {}  /*gameCodes()*/

void Server::run() {
    acep_th.start();

    std::string input;
    while (std::cin >> input) {
        if (input == "q") {
            break;
        }
    }
}

Server::~Server(){
    acep_th.shutdown();
    acep_th.join();
    svr_socket.close(); //creo que no lo necesitamos
}

