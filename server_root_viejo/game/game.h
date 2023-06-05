#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include "queue.h"
#include "../entities/player.h"
#include "../entities/entity.h"
#include <iostream>
#include <utility>
#include <string>
#include <mutex>
#include <vector>
#include <map>
#include <memory>

#define TAM_MAX_COLA 20

typedef struct gameStateDTO gameStateDTO_t;

struct gameStateDTO {
    std::shared_ptr<std::vector<std::shared_ptr<entity_t>>> entities;
};

class Game {
    private:
    unsigned int code;
    std::vector<Queue<std::shared_ptr<gameStateDTO_t>>*> game;
    std::map<int, Entity*> entities;

    void getGameStateDTO(std::shared_ptr<gameStateDTO_t>* gameStateDTO);

    public:
    explicit Game(unsigned int code);

    void sendStateGame();

    void update();

    bool addEntity(Queue<std::shared_ptr<gameStateDTO_t>>* queue, int idEntity);

    const int getCode();
    
    void startMove(int dirX, int dirY, int idPlayer);

    void endMove(int idPlayer);
};


#endif
