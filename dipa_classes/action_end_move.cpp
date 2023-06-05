#include "action_end_move.h"

EndMove::EndMove(int idPlayer) : idPlayer(idPlayer){}

actionDTO_t* EndMove::getDTO() const {
    EndMoveDTO_t* dto = new(EndMoveDTO_t);
    dto->idPlayer = idPlayer;

    actionDTO_t* dtoAction = new(actionDTO_t);
    dtoAction->type = END_MOVE;
    dtoAction->dto = (void*)dto;
    return dtoAction;
}

/*void EndMove::run(Game& game) {
    game.endMove(idPlayer);
}*/