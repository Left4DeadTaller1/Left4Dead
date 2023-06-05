#include "entity.h"

Entity::Entity(int xPosition, int yPosition, int width, int height)
    : x(xPosition), y(yPosition), width(width), height(height), health(100), movementState(ENTITY_IDLE), movementDirectionX(NONE_X), movementDirectionY(NONE_Y) {
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

int Entity::getMovementSpeed() {
    return 5;
}

void Entity::move(int deltaX, int deltaY) {
    x += deltaX;
    y += deltaY;
}

Entity::~Entity() {
}