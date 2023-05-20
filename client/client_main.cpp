//  Copyright NULL

#include <stdio.h>
#include <iostream>
#include "client.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#define WIDTH_WINDOW 1000
#define HEIGHT_WINDOW 800

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

    //ver si se puede mover a otro lado
    SDL sdl(SDL_INIT_VIDEO);

	Window window("Left4Dead",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIDTH_WINDOW, HEIGHT_WINDOW,
			SDL_WINDOW_RESIZABLE);

    Client client(hostname, servname, window);
    client.run();
    ret = 0;
    return ret;
}