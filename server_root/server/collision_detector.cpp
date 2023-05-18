#include "collision_detector.h"

CollisionDetector::CollisionDetector() {}

CollisionDetector::~CollisionDetector() {}

bool CollisionDetector::isColliding(Entity& e1, Entity& e2) {
    if (e1.x < e2.x + e2.width &&
        e1.x + e1.width > e2.x &&
        e1.y < e2.y + e2.height &&
        e1.y + e1.height > e2.y) {
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

std::vector<Entity*> CollisionDetector::getBeingShot(Shot& bullet, std::vector<Entity*>& entities) {
    std::vector<Entity*> entitiesBeingShot;

    for (Entity* entity : entities) {
        if ((bullet.shootingLeft() && entity->x > bullet.xOrigin) ||
            (!bullet.shootingLeft() && entity->x < bullet.xOrigin)) {
            continue;
        }

        if ((entity->y < bullet.lowerY && bullet.lowerY < entity->y + entity->height) ||
            (entity->y < bullet.upperY && bullet.upperY < entity->y + entity->height)) {
            entitiesBeingShot.push_back(entity);
        }
    }
    // The logic for the dmg taken should be in the game class, this method just returns the entities that are being shot
    return entitiesBeingShot;
}
