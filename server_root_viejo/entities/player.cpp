#include "player.h"

Player::Player(int idPlayer, int xPosition, int yPosition, int width, int height)
    : Entity(idPlayer, xPosition, yPosition, width, height) {
}

void Player::startMove(int dirX, int dirY) {
    this->dirX = dirX;
    this->dirY = dirY;
}

void Player::endMove() {
    this->dirX = 0;
    this->dirY = 0;
}

void Player::updatePosition(){
    //casos limite
    x = x + dirX;
    y = y + dirY;
}

void Player::updateState(){
    if (dirX != 0 || dirY != 0){
        state = WALKING;
    } else {
        state = IDLE;
    }
}

void Player::update() {
    updatePosition();
    updateState();
}