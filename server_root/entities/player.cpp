#include "player.h"

Player::Player(int xPosition, int yPosition, int width, int height, std::string idPlayer)
    : Entity(xPosition, yPosition, width, height, idPlayer), weaponState(WEAPON_IDLE), bullets(10) {
}

EntityType Player::getType() {
    return PLAYER;
}

WeaponState Player::getWeaponState() {
    return weaponState;
}

void Player::setWeaponState(WeaponState weaponState) {
    this->weaponState = weaponState;
}

std::shared_ptr<EntityDTO> Player::getDto() {
    auto dto = std::make_shared<PlayerDTO>();
    dto->type = PLAYER;
    dto->id = this->getId();
    dto->x = this->getX();
    dto->y = this->getY();
    dto->health = this->getHealth();
    dto->movementState = static_cast<int>(this->getMovementState());
    dto->movementDirectionX = static_cast<int>(this->getMovementDirectionX());
    dto->healthState = static_cast<int>(this->getHealthState());
    dto->weaponState = this->getWeaponState();
    return dto;
}

void Player::decreaseAtkCooldown() {
    if (atkCooldown > 0) {
        atkCooldown--;
    }
}

bool Player::canAttack() {
    if (bullets > 0 && atkCooldown == 0) {
        return true;
    } else {
        return false;
    }
}

Shot Player::shoot() {
    bullets--;
    atkCooldown = 10;
    // TODO: cambia esto a enum
    std::string bulletDirection;

    switch (movementDirectionX) {
        case ENTITY_LEFT:
            bulletDirection = "left";
            break;
        case ENTITY_RIGHT:
            bulletDirection = "right";
            break;
        default:
            break;
    }
    return Shot(false, 10, x, bulletDirection, y, y + height);
}

Player::~Player() {
}