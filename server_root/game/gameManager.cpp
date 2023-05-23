//#include "server_games.h"
#include <iostream>
#include <string>

//en esta clase hay cosas que no estan buenas, lo pongo solo para ver si funciona la conexion del lado del cliente

GamesManager::GamesManager(unsigned int n) : contador(n){}

Game* GamesManager::create(const std::string& name, Queue<std::string>* queue){
    std::unique_lock<std::mutex> lck(m);
    games[contador] = new Game(contador);
    (*games[contador]).add_queue(queue);
    contador += 1;
    return games[code];
}

Game* GamesManager::join(int code, Queue<std::string>* queue){
    std::unique_lock<std::mutex> lck(m);
    if (code >= (int)contador || code < 0){
        return 1;
    }
    (*games[code]).add_queue(queue);
    return games[code];
}

void GamesManager::delete_all_games(void){
    std::unique_lock<std::mutex> lck(m);
    for (auto &kv : games) {
        delete kv.second;
    }
}