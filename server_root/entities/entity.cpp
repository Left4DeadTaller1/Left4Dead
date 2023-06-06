#include "entity.h"

Entity::Entity(int xPosition, int yPosition, int width, int height, std::string id)
    : x(xPosition), y(yPosition), width(width), height(height), health(100), entityId(id) movementState(ENTITY_IDLE), movementDirectionX(ENTITY_NONE_X), movementDirectionY(ENTITY_NONE_Y), healthState(ALIVE) {
}

MovementState Entity::getMovementState() {
    return movementState;
}

MovementDirectionX Entity::getMovementDirectionX() {
    return movementDirectionX;
}

MovementDirectionY Entity::getMovementDirectionY() {
    return movementDirectionY;
}

HealthState Entity::getHealthState() {
    return healthState;
}

int Entity::getMovementSpeed() {
    return 5;
}

void Entity::move(int deltaX, int deltaY) {
    x += deltaX;
    y += deltaY;
}

void Entity::setMovementState(MovementState movementState) {
    this->movementState = movementState;
}

void Entity::setMovementDirectionX(MovementDirectionX movementDirectionX) {
    this->movementDirectionX = movementDirectionX;
}

void Entity::setMovementDirectionY(MovementDirectionY movementDirectionY) {
    this->movementDirectionY = movementDirectionY;
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

Entity::~Entity() {
}