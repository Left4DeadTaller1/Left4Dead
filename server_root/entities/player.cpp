#include "player.h"

Player::Player(int xPosition, int yPosition, int width, int height, std::string idPlayer)
    : Entity(xPosition, yPosition, width, height), idPlayer(idPlayer), weaponState(WEAPON_IDLE) {
}

void Player::move(int deltaX, int deltaY) {
    // restricciones de movimento
    x += deltaX;
    y += deltaY;
}

std::string Player::getPlayerId() {
    return idPlayer;
}

Player::~Player() {
}