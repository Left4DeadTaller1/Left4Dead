//  Copyright NULL

#include <exception>
#include <iostream>
#include <string>

#include "server.h"

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: ./server <servicename/port>" << std::endl;
            return 1;
        }
        const char *servname = argv[1];
        Server server(servname);
        server.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }
    return 0;
}