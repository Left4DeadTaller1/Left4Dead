#include "move.h"

Move::Move(int idPlayer, int deltaX, int deltaY) : idPlayer(idPlayer),
                                                   deltaX(deltaX),
                                                   deltaY(deltaY) {}

void Move::run(Game& Game) {
    //     gameState.move(deltaX, deltaY, idPlayer);
}