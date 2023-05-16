//  Copyright NULL

#include <exception>
#include <iostream>
#include <string>

#include "server.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./server <servicename/port>" << std::endl;
        return 1;
    }
    const char *servname = argv[1];
    Server server(servname);
    server.run();
    return 0;
}