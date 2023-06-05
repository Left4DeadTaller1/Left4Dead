//  Copyright NULL

#include <iostream>
#include <exception>
#include "server.h"

int main(int argc, char *argv[]) {
    int ret = -1;

    if (argc != 2) {
        std::cerr << "Errror en la cantidad de argumentos\n";
        return ret;
    }

    const char *servname = argv[1];
    Server server(servname);
    server.launch_server();

    ret = 0;
    return ret;
}