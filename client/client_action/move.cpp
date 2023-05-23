#include "move.h"

Move::Move(int idPlayer, int deltaX, int deltaY) : idPlayer(idPlayer),
                                                   deltaX(deltaX),
                                                   deltaY(deltaY) {}

//creo que desp voy a necesitar mandar el id del player
int Move::send(ClientProtocol& protocol, bool& wasClosed) {
    protocol.move(deltaX, deltaY, wasClosed);
    return 0;
}