#include "move.h"

Move::Move(int idPlayer, int difx, int dify): idPlayer(idPlayer),
                                                difx(difx),
                                                dify(dify){}

void Move::run(GameState& gameState){
    gameState.move(difx, dify, idPlayer);
}