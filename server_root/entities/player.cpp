#include "player.h"

#include "game_config.h"

Player::Player(int xPosition, int yPosition, std::string playerId, WeaponType weaponType, std::string nickName)
    : Entity(xPosition, yPosition, playerId), weapon(weaponType), actionState(PLAYER_IDLE), nickName(nickName), knockDowns(0), revivingPlayer(nullptr), framesAfk(0) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["PLAYER_WIDTH"];
    height = entityParams["PLAYER_HEIGHT"];
    health = entityParams["PLAYER_HEALTH"];
    movementSpeed = entityParams["PLAYER_SPEED"];
}

LobbyPlayerDTO Player::getLobbyDto() {
    LobbyPlayerDTO lobbyDto;
    lobbyDto.id = this->entityId;
    lobbyDto.nickName = this->nickName;
    lobbyDto.weaponType = static_cast<int>(weapon.getType());
    return lobbyDto;
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
            yAmount = movementSpeed;
            break;

        case ENTITY_DOWN:
            yAmount = -movementSpeed;
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

std::shared_ptr<Player> Player::getClosestRevivablePlayer(std::vector<std::shared_ptr<Player>>& players) {
    if (players.size() <= 1) {
        return nullptr;
    }

    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    int maxRevivalDistance = entityParams["PLAYER_REVIVE_DISTANCE"];
    int distanceToClosestPlayer;
    // this gets initialized bc of shortcircuiting

    std::shared_ptr<Player> closestRevivablePlayer = nullptr;

    for (const auto& player : players) {
        if (player.get() == this || player->getActionState() != PLAYER_DYING) continue;

        int distance = std::sqrt(std::pow((x - player->getX()), 2) + std::pow((y - player->getY()), 2));

        if (distance <= maxRevivalDistance && (closestRevivablePlayer == nullptr || distance < distanceToClosestPlayer)) {
            closestRevivablePlayer = player;
            distanceToClosestPlayer = distance;
        }

        return closestRevivablePlayer;
    }
    return nullptr;
}

std::shared_ptr<Player> Player::getRevivingPlayer() {
    return revivingPlayer;
}

void Player::setClosestRevivablePlayer(std::shared_ptr<Player> player) {
    this->revivingPlayer = player;
}

void Player::setRevivalState() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    this->actionState = PLAYER_REVIVING;
    this->actionCounter = entityParams["PLAYER_REVIVAL_DURATION"];
}

void Player::revive() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    this->actionState = PLAYER_IDLE;
    this->health = (entityParams["PLAYER_HEALTH"] / 2);
}

bool Player::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = PLAYER_DYING;
        actionCounter = entityParams["PLAYER_DYING_DURATION"];
        knockDowns++;
        return true;
    } else {
        actionState = PLAYER_HURT;
        actionCounter = entityParams["PLAYER_HURT_DURATION"];
        return false;
    }
    return false;
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
    dto->weaponType = static_cast<int>(weapon.getType());
    dto->bullets = this->weapon.getBullets();
    dto->nickName = this->nickName;
    return dto;
}

void Player::startMoving() {
    actionState = PLAYER_WALKING;
}

void Player::decreaseATKCooldown() {
    weapon.decreaseCooldown();
}

void Player::idle() {
    actionState = PLAYER_IDLE;
}

void Player::reload() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    weapon.reload();
    actionCounter = entityParams["PLAYER_RELOAD_DURATION"];
}

bool Player::canAttack() {
    if (actionCounter != 0)
        return false;
    return weapon.canShoot();
}

void Player::decreaseActionCounter() {
    // TODO remove this one
    if (actionCounter > 0) {
        actionCounter--;
        if (actionCounter == 0 && !isMoving() && !isDead())
            idle();
    } else if (checkIfDead())
        kill();
}

Attack Player::generateAttack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    AttackDirection attackDirection = RIGHT;  // some default values to avoid warnings

    switch (facingDirection) {
        case FACING_LEFT:
            attackDirection = LEFT;
            break;
        case FACING_RIGHT:
            attackDirection = RIGHT;
            break;
    }

    // return weapon.shoot(x, attackDirection, y, y + height);
    Attack bullet = weapon.shoot(x, attackDirection, y, (y + height));
    actionCounter = weapon.getCooldown();

    return bullet;
}

int Player::getWeaponDamageFalloff() {
    return weapon.getDamageFalloff();
}

void Player::increaseAfkTimer() {
    framesAfk++;
}

void Player::resetAfkTimer() {
    framesAfk = 0;
}

int Player::getAfkTimer() {
    return framesAfk;
}

bool Player::checkIfDead() {
    // TODO test knockdowns
    if ((actionState == PLAYER_DYING && actionCounter == 0) || (actionState == PLAYER_DYING && knockDowns >= 3))
        return true;

    return false;
}

void Player::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = PLAYER_DEAD;
    actionCounter = entityParams["PLAYER_DEATH_DURATION"];
}

bool Player::isDead() {
    return (actionState == PLAYER_DEAD || actionState == PLAYER_DYING);
}

bool Player::isRemovable() {
    return (actionCounter == 0 && actionState == PLAYER_DEAD);
}

std::string Player::getNickName() {
    return nickName;
}

Player::~Player() {
}