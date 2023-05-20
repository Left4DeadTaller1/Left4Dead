#include "player.h"

Player::Player(int xPosition, int yPosition, int width, int height)
    : Entity(xPosition, yPosition, width, height) {}

void Player::move(int deltaX, int deltaY) {
    // restricciones de movimento
    x += deltaX;
    y += deltaY;
}