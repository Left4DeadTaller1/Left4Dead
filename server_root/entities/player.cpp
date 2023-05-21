#include "player.h"

Player::Player(int xPosition, int yPosition, int width, int height, int idPlayer)
    : Entity(xPosition, yPosition, width, height), idPlayer(idPlayer) {
}

void Player::move(int deltaX, int deltaY) {
    // restricciones de movimento
    x += deltaX;
    y += deltaY;
}