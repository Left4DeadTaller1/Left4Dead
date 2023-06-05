#include "game.h"

Game::Game(unsigned int code) : code(code){}

void Game::startMove(int dirX, int dirY, int idPlayer){
    (entities[idPlayer])->startMove(dirX, dirY);
}

void Game::endMove(int idPlayer){
    (entities[idPlayer])->endMove();
}

void Game::update(){
    for (auto &ent : entities){
        ent.second->update();
    }
}

void Game::getGameStateDTO(std::shared_ptr<gameStateDTO_t>* gameStateDTO){
    for (auto &ent : entities){
        std::shared_ptr<entity_t> entity = std::make_shared<entity_t>();
        ent.second->getEntityDTO(&entity);
        ((*gameStateDTO)->entities)->push_back(entity);
    }
    return;
}

void Game::sendStateGame(){
    std::shared_ptr<gameStateDTO_t> gameStateDTO = std::make_shared<gameStateDTO_t>();
    std::shared_ptr<std::vector<std::shared_ptr<entity_t>>> entities = std::make_shared<std::vector<std::shared_ptr<entity_t>>>();
    gameStateDTO->entities = entities;
    getGameStateDTO(&gameStateDTO);
    for (Queue<std::shared_ptr<gameStateDTO_t>>* queue : game) {
        (*queue).push(gameStateDTO);
    }
    return;
}

bool Game::addEntity(Queue<std::shared_ptr<gameStateDTO_t>>* queue, int idPlayer){
    std::cout << "se agrega una etnidad al juego\n";
    game.push_back(queue);
    std::cout << "pasa el pushback\n";
    std::cout << "id player: " << idPlayer << "\n";
    Entity* entity = new Player(idPlayer, 0, 0, 10, 10);
    std::cout << "pasa new player\n";
    entities[idPlayer] = entity;
    std::cout << "pasa entities[idPlayer] = entity\n";
    return true;
}

const int Game::getCode(){
    return code;
}
