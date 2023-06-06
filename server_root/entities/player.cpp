#include "player.h"

Player::Player(int xPosition, int yPosition, int width, int height, std::string idPlayer)
    : Entity(xPosition, yPosition, width, height, idPlayer), weaponState(WEAPON_IDLE) {
}

std::string Player::getType() {
    return "player";
}

WeaponState Player::getWeaponState() {
    return weaponState;
}

Player::~Player() {
}