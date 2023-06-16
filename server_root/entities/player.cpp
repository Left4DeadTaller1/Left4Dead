#include "player.h"

#include "game_config.h"

Player::Player(int xPosition, int yPosition, std::string playerId, WeaponType weaponType)
    : Entity(xPosition, yPosition, playerId), weaponState(WEAPON_IDLE), weapon(weaponType), actionState(IDLE_STATE) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["PLAYER_WIDTH"];
    height = entityParams["PLAYER_HEIGHT"];
    health = entityParams["PLAYER_HEALTH"];
    movementSpeed = entityParams["PLAYER_SPEED"];
}

EntityType Player::getType() {
    return PLAYER;
}

WeaponState Player::getWeaponState() {
    return weaponState;
}

void Player::setMovementState(MovementState movementState) {
    this->movementState = movementState;
}

void Player::setMovementDirectionX(MovementDirectionX movementDirectionX) {
    switch (movementDirectionX) {
        case ENTITY_LEFT:
            facingDirection = FACING_LEFT;
            break;

        case ENTITY_RIGHT:
            facingDirection = FACING_RIGHT;
            break;

        default:
            break;
    }
    this->movementDirectionX = movementDirectionX;
}

void Player::setMovementDirectionY(MovementDirectionY movementDirectionY) {
    this->movementDirectionY = movementDirectionY;
}

void Player::setWeaponState(WeaponState weaponState) {
    this->weaponState = weaponState;
}

std::shared_ptr<EntityDTO> Player::getDto() {
    auto dto = std::make_shared<PlayerDTO>();
    dto->type = PLAYER;
    dto->id = this->entityId;
    dto->x = this->x;
    dto->y = this->y;
    dto->health = this->health;
    dto->movementState = static_cast<int>(this->getMovementState());
    dto->movementDirectionX = static_cast<int>(this->getMovementDirectionX());
    dto->healthState = static_cast<int>(this->getHealthState());
    dto->facingDirection = this->facingDirection;
    dto->weaponState = this->weaponState;
    dto->bullets = this->weapon.getBullets();
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

    switch (facingDirection) {
        case FACING_LEFT:
            attackDirection = LEFT;
            break;
        case FACING_RIGHT:
            attackDirection = RIGHT;
            break;
    }

    return weapon.shoot(x, attackDirection, y, y + height);
}

Player::~Player() {
}