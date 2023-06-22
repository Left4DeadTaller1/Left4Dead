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
    if (actionCounter > 0)
        actionCounter--;
    else if (checkIfDead())
        kill();
    else if (actionCounter == 0 && !isMoving())
        idle();
}

std::shared_ptr<EntityDTO> Entity::getDto() {
    auto dto = std::make_shared<EntityDTO>();
    return dto;
}

Entity::~Entity() {
}