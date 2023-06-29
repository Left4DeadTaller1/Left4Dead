//  Copyright NULL

#include <SDL2pp/SDL2pp.hh>
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include "client.h"
#include "client_protocol.h"
#include "menuQT/mainwindow.h"
#include "renderer_config.h"

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

    ClientProtocol protocol(hostname, servname);

    QApplication a(argc, argv);
    MainWindow windowQT(protocol);
    windowQT.show();
    ret = a.exec();
    
    if (ret == 0){
        RendererConfig& config = RendererConfig::getInstance();
        std::map<std::string, int> dimensionsWindows = config.getDimensionsWindows();

        SDL2pp::SDL sdl(SDL_INIT_EVERYTHING);

        SDL2pp::Window window("Left4Dead",
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    dimensionsWindows["WINDOW_WIDTH"], 
                    dimensionsWindows["WINDOW_HEIGHT"],
                    SDL_WINDOW_RESIZABLE);

        Client client(hostname, servname, window, protocol, windowQT);
        client.run();
    }
    return ret;

    } catch (const std::exception &e) {
        std::cerr << "Client Main: Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client Main: Unknown exception caught. Ending program." << std::endl;
    }
}
