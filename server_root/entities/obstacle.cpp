#include "obstacle.h"

Obstacle::Obstacle(int xPosition, int yPosition, std::string obstacleId, int height, int width)
    : Entity(xPosition, yPosition, obstacleId) {
    height = height;
    width = width;
}

bool Obstacle::isAttackable() {
    return false;
}

EntityType Obstacle::getType() {
    return OBSTACLE;
}

bool Obstacle::isMoving() {
    return false;
}

bool Obstacle::takeDamage(int amountOfDamage) {
    return false;
}

void Obstacle::decreaseATKCooldown() {
    return;
}

bool Obstacle::checkIfDead() {
    return false;
}

void Obstacle::kill() {
    return;
}

bool Obstacle::isDead() {
    return false;
}

bool Obstacle::isRemovable() {
    return false;
}

void Obstacle::idle() {
    return;
}

Attack Obstacle::generateAttack() {
    return Attack(MELEE, 0, x, facingDirection, y, y, 0);
}

void Obstacle::startMoving() {
    return;
}

std::tuple<int, int> Obstacle::getDirectionsAmount() {
    return std::make_tuple(0, 0);
}

bool Obstacle::canAttack() {
    return false;
}
