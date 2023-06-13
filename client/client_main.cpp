//  Copyright NULL

#include <SDL2pp/SDL2pp.hh>
#include <stdio.h>
#include <iostream>
#include "client.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("Left4Dead",
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  WINDOW_WIDTH, WINDOW_HEIGHT,
                  SDL_WINDOW_RESIZABLE);

    Client client(hostname, servname, window);
    client.run();
    ret = 0;
    return ret;
}