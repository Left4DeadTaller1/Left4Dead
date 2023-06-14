#include "entity.h"

Entity::Entity(int xPosition, int yPosition, std::string id)
    : x(xPosition), y(yPosition), entityId(id), movementState(ENTITY_IDLE), movementDirectionX(ENTITY_RIGHT), movementDirectionY(ENTITY_UP), facingDirection(FACING_RIGHT), healthState(ALIVE), framesHurt(15) {
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

void Entity::setHealthState(HealthState healthState) {
    if (framesHurt == 0)
        this->healthState = healthState;
    else
        framesHurt--;
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

std::shared_ptr<EntityDTO> Entity::getDto() {
    auto dto = std::make_shared<EntityDTO>();
    return dto;
}

void Entity::takeDamage(int amountOfDamage) {
    health -= amountOfDamage;
    healthState = HURT;
    /// TODO do this:
    // if (health <= 0) {
    //     healthState = DYING;
    // }
}

Entity::~Entity() {
}