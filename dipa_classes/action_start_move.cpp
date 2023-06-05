#include "action_start_move.h"

StartMove::StartMove(int idPlayer, int dirX, int dirY) : idPlayer(idPlayer),
                                                   dirX(dirX),
                                                   dirY(dirY) {}

actionDTO_t* StartMove::getDTO() const {
    StartMoveDTO_t* dto = new(StartMoveDTO_t);
    dto->idPlayer = idPlayer;
    dto->dirX = dirX;
    dto->dirY = dirY;

    actionDTO_t* dtoAction = new(actionDTO_t);
    dtoAction->type = START_MOVE;
    dtoAction->dto = (void*)dto;
    return dtoAction;
}

/*void StartMove::run(Game& game) {
    game.startMove(dirX, dirY, idPlayer);
}*/