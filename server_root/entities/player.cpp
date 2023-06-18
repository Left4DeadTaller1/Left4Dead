#include "player.h"

#include "game_config.h"

Player::Player(int xPosition, int yPosition, std::string playerId, WeaponType weaponType)
    : Entity(xPosition, yPosition, playerId), weapon(weaponType), actionState(PLAYER_IDLE) {
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

bool Player::isMoving() {
    return actionState == PLAYER_WALKING || actionState == PLAYER_RUNNING;
}

std::tuple<int, int> Player::getDirectionsAmount() {
    int xAmount = 0;
    int yAmount = 0;

    switch (movementDirectionX) {
        case ENTITY_LEFT:
            xAmount = -movementSpeed;
            break;

        case ENTITY_RIGHT:
            xAmount = movementSpeed;
            break;

        default:
            break;
    }

    switch (movementDirectionY) {
        case ENTITY_UP:
            yAmount = -movementSpeed;
            break;

        case ENTITY_DOWN:
            yAmount = movementSpeed;
            break;

        default:
            break;
    }

    if (actionState == PLAYER_RUNNING) {
        xAmount *= 2;
        yAmount *= 2;
    }

    return std::make_tuple(xAmount, yAmount);
}

void Player::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = PLAYER_DYING;
        actionCounter = entityParams["PLAYER_DYING_DURATION"];
    } else {
        actionState = PLAYER_HURT;
        actionCounter = entityParams["PLAYER_HURT_DURATION"];
    }
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

void Player::setActionState(PlayerActionState actionState) {
    this->actionState = actionState;
}

PlayerActionState Player::getActionState() {
    return actionState;
}

std::shared_ptr<EntityDTO> Player::getDto() {
    auto dto = std::make_shared<PlayerDTO>();
    dto->type = PLAYER;
    dto->id = this->entityId;
    dto->x = this->x;
    dto->y = this->y;
    dto->health = this->health;
    dto->actionState = this->actionState;
    dto->actionCounter = this->actionCounter;
    // TODO check if i need to remove this one
    dto->movementDirectionX = static_cast<int>(this->getMovementDirectionX());
    dto->facingDirection = this->facingDirection;
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

void Player::checkIfDead() {
    if (actionState == PLAYER_DYING && actionCounter == 0) {
        kill();
    }
}

void Player::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = PLAYER_DEAD;
    actionCounter = entityParams["PLAYER_DEATH_DURATION"];
}

Player::~Player() {
}