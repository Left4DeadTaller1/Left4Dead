#include "player.h"

#include "game_config.h"

Player::Player(int xPosition, int yPosition, std::string playerId, WeaponType weaponType)
    : Entity(xPosition, yPosition, playerId), weaponState(WEAPON_IDLE), weapon(weaponType) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["PLAYER_WIDTH"];
    height = entityParams["PLAYER_HEIGHT"];
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

void Player::decreaseATKCooldown() {
    weapon.decreaseCooldown();
}

bool Player::canAttack() {
    return weapon.canShoot();
}

Attack Player::attack() {
    AttackDirection attackDirection = RIGHT;  // some default values to avoid warnings

    switch (movementDirectionX) {
        case ENTITY_LEFT:
            attackDirection = LEFT;
            break;
        case ENTITY_RIGHT:
            attackDirection = RIGHT;
            break;
    }

    return weapon.shoot(x, attackDirection, y, y + height);
}

Player::~Player() {
}