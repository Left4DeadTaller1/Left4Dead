#include "entity.h"

Entity::Entity(int xPosition, int yPosition, int width, int height, std::string id)
    : x(xPosition), y(yPosition), width(width), height(height), health(100), entityId(id), movementState(ENTITY_IDLE), movementDirectionX(ENTITY_RIGHT), movementDirectionY(ENTITY_UP), healthState(ALIVE), atkCooldown(10) {
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

std::shared_ptr<EntityDTO> Entity::getDto() {
    auto dto = std::make_shared<EntityDTO>();
    return dto;
}

void Entity::takeDamage(int amountOfDamage) {
    health -= amountOfDamage;
    /// TODO do this:
    // if (health <= 0) {
    //     healthState = DYING;
    // }
}

void Entity::decreaseATKCooldown() {
    if (atkCooldown > 0)
        atkCooldown--;
}

Entity::~Entity() {
}