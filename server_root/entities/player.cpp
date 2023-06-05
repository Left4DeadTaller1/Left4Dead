#include "player.h"

Player::Player(int xPosition, int yPosition, int width, int height, std::string idPlayer)
    : Entity(xPosition, yPosition, width, height), idPlayer(idPlayer), state(IDLE) {
}

void Player::move(int deltaX, int deltaY) {
    // restricciones de movimento
    x += deltaX;
    y += deltaY;
}

std::string Player::getId() {
    return idPlayer;
}

Player::~Player() {
}