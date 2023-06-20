//  Copyright NULL

#include <SDL2pp/SDL2pp.hh>
#include "../mainwindow.h"
#include "../SdlWindow.h"
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include "client.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[]) { try {
    int ret = -1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected "
                  << argv[0]
                  << " with 2 arguments.\n";
        return ret;
    }
    const char *hostname = argv[1];
    const char *servname = argv[2];

    std::shared_ptr<ActionClient> startAction;
    QApplication a(argc, argv);
    MainWindow w(startAction);
    w.show();
    ret = a.exec();

    SDL2pp::SDL sdl(SDL_INIT_EVERYTHING);

    SDL2pp::Window window("Left4Dead",
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  WINDOW_WIDTH, WINDOW_HEIGHT,
                  SDL_WINDOW_RESIZABLE);

    Client client(hostname, servname, window);
    client.run();
    return ret;

    } catch (const std::exception &e) {
        std::cerr << "Client Main: Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client Main: Unknown exception caught. Ending program." << std::endl;
    }
}

/*unsigned int winId = w.getWinId();
if (!winId) {
    return ret;
}

SdlWindow sdlWindow((void*) &winId);
sdlWindow.fill(0x33,0x66,0x99, 0xFF);
sdlWindow.render();
SDL_Renderer* renderer = sdlWindow.getRenderer();
SDL_Window* window_ = sdlWindow.getWindow();

try {
    SDL2pp::Window window(window_);
    Client client(hostname, servname, window);
    client.run();

} catch (const SDL2pp::Exception& e) {
    std::cerr << "Error\n";
    return ret;
}*/