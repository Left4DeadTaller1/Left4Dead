#include "player.h"

Player::Player(int posxInicial, int posyInicial): posx(posxInicial), 
                                        posy(posyInicial) {}

void Player::move(int deltaX, int deltaY){
    //restricciones de movimento
    posx += deltaX;
    posy += deltaY;
}