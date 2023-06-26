#include "entity.h"
Entity::Entity(int xPosition, int yPosition, std::string id)
    : x(xPosition), y(yPosition), entityId(id), movementDirectionX(ENTITY_NONE_X), movementDirectionY(ENTITY_NONE_Y), facingDirection(FACING_RIGHT), actionCounter(0) {
}

MovementDirectionX Entity::getMovementDirectionX() {
    return movementDirectionX;
}

MovementDirectionY Entity::getMovementDirectionY() {
    return movementDirectionY;
}

int Entity::getMovementSpeed() {
    return movementSpeed;
}

bool Entity::facingLeft() {
    return facingDirection == FACING_LEFT;
}

bool Entity::facingRight() {
    return facingDirection == FACING_RIGHT;
}

bool Entity::isAttackable() {
    return true;
}

void Entity::useSkill(std::vector<std::shared_ptr<Entity>> &players) {
    return;
}

void Entity::move(int deltaX, int deltaY) {
    x += deltaX;
    y += deltaY;
}

std::string Entity::getId() {
    return entityId;
}

int Entity::getX() {
    return x;
}

int Entity::getY() {
    return y;
}

int Entity::getHealth() {
    return health;
}

int Entity::getActionCounter() {
    return actionCounter;
}

void Entity::decreaseActionCounter() {
    if (actionCounter > 0) {
        actionCounter--;
    }

    if (checkIfDead()) {
        kill();
        return;
    }
    if (actionCounter == 0 && !isMoving() && !isDead())
        idle();
}

std::shared_ptr<EntityDTO> Entity::getDto() {
    auto dto = std::make_shared<EntityDTO>();
    return dto;
}

Entity::~Entity() {
}