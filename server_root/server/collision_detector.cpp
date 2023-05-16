#include "collision_detector.h"

CollisionDetector::CollisionDetector() {}

CollisionDetector::~CollisionDetector() {}

bool CollisionDetector::isColliding(Entity& e1, Entity& e2) {
    if (e1.getX() < e2.getX() + e2.getWidth() &&
        e1.getX() + e1.getWidth() > e2.getX() &&
        e1.getY() < e2.getY() + e2.getHeight() &&
        e1.getY() + e1.getHeight() > e2.getY()) {
        return true;
    }
    return false;
}

std::vector<Entity*> CollisionDetector::getCollisions(Entity& entity, std::vector<Entity*>& entities) {
    std::vector<Entity*> collisions;

    // Check for collision between entity and all other entities
    for (Entity* other : entities) {
        if (&entity != other && isColliding(entity, *other)) {
            collisions.push_back(other);
        }
    }

    return collisions;
}
