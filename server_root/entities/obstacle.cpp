#include "obstacle.h"

Obstacle::Obstacle(int xPosition, int yPosition, std::string obstacleId)
    : Entity(xPosition, yPosition, obstacleId) {
}

bool Obstacle::isAttackable() {
    return false;
}

EntityType Obstacle::getType() {
    return OBSTACLE;
}