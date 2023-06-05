#include "action_start_game.h"

actionDTO_t* StartGame::getDTO() const {
    actionDTO_t* dtoAction = new(actionDTO_t);
    dtoAction->type = START_GAME;
    return dtoAction;
}

/*void StartGame::run(Game& game) {
    return;
}*/