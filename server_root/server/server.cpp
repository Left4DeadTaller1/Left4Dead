#include "server.h"
// #define SHUT_RDWR 2

#include <cstring>
#include <iostream>
#include <string>

#include "acceptor.h"

Server::Server(const char *servname) : svr_socket(servname) /*gameCodes()*/ {}
void Server::run() {
    Acceptor acep_th(svr_socket /*, gameCodes*/);
    acep_th.start();
    std::string input;
    while (std::cin >> input) {
        if (input == "q") {
            break;
        }
    }
    acep_th.shutdown();
    acep_th.join();
    svr_socket.close();
}
