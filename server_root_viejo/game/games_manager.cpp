#include "games_manager.h"
#include <iostream>
#include <string>

GameManager::GameManager(unsigned int n) : contador(n){}

Game* GameManager::create(const std::string& name, Queue<std::shared_ptr<gameStateDTO_t>>* qClient, int idEntity){
    std::unique_lock<std::mutex> lck(m);
    gameManager[contador] = new Game(contador);
    (*gameManager[contador]).addEntity(qClient, idEntity);
    contador += 1;
    return gameManager[contador - 1];
}

Queue<Action*>* GameManager::join(int code, Queue<std::shared_ptr<gameStateDTO_t>>* qClient, int idEntity){
    std::unique_lock<std::mutex> lck(m);
    if (code >= (int)contador || code < 0){
        return NULL;
    }
    (*gameManager[code]).addEntity(qClient, idEntity);
    std::cout << "sale de addEntuty\n";
    return qActionsGames[code];
}

void GameManager::delete_all_gameManager(void){
    for (auto &kv : gameManager) {
        delete kv.second;
    }
}

Queue<Action*>* GameManager::startGame(int code) {
    Queue<Action*>* qActions = new Queue<Action*>(1000);
    qActionsGames[code] = qActions;
    GameThread* gameThread = new GameThread(gameManager[code], qActions);
    gameThread->start();
    return qActions;
}
