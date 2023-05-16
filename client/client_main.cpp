//  Copyright NULL

#include <stdio.h>

#include <iostream>

#include "client.h"

int main(int argc, char *argv[]) {
    int ret = -1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected "
                  << argv[0]
                  << " with 2 arguments.\n";
        return ret;
    }
    const char *hostname = argv[1];
    const char *servname = argv[2];
    Client client(hostname, servname);
    client.run();
    ret = 0;
    return ret;
}