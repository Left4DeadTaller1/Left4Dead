#include "server.h"

Server::Server(const std::string& servname) : protocol(servname), skt(servname.c_str()) {}

void Server::launch_server(void){
    GameManager gameManager(GAME_COUNTER_START);

    Acceptor* listener = new Acceptor(std::move(skt), gameManager, protocol);
    listener->start();

    char c = ' ';
    while (c != 'q'){
        c = std::cin.get();
    }
    listener->stop();
    listener->join();
    delete listener;

    gameManager.delete_all_gameManager();
}
