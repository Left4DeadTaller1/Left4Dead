#include "collision_detector.h"

CollisionDetector::CollisionDetector() {}

CollisionDetector::~CollisionDetector() {}

bool CollisionDetector::isColliding(Entity& e1, int deltaX, int deltaY, Entity& e2) {
    // discard cuz they are not in the same "depth"
    if ((e1.y + deltaY) + e1.height < e2.y || (e1.y + deltaY) > e2.y + e2.height) {
        return false;
    }
    // discard cuz they are not close in the x axis
    if ((e1.x + deltaX) + e1.width < e2.x || (e1.x + deltaX) > e2.x + e2.width) {
        return false;
    }

    // the rectangules are touching or overlapping
    if ((e1.x + deltaX) + e1.width >= e2.x && (e1.x + deltaX) <= e2.x + e2.width &&
        (e1.y + deltaY) + e1.height >= e2.y && (e1.y + deltaY) <= e2.y + e2.height) {
        return true;
    }

    return false;
}

bool CollisionDetector::checkForCollisions(Entity& entity, int deltaX, int deltaY, std::vector<std::shared_ptr<Entity>>& entities) {
    for (auto& other : entities) {
        if (&entity != other.get() && isColliding(entity, deltaX, deltaY, *other)) {
            return true;
        }
    }

    return false;
}

std::list<std::shared_ptr<Entity>> CollisionDetector::getBeingShot(Shot& bullet, std::vector<std::shared_ptr<Entity>>& entities) {
    std::list<std::shared_ptr<Entity>> entitiesBeingShot;

    for (const auto& entity : entities) {
        if ((bullet.shootingLeft() && entity->x > bullet.xOrigin) ||
            (!bullet.shootingLeft() && entity->x < bullet.xOrigin)) {
            continue;
        }

        if ((entity->y < bullet.lowerY && bullet.lowerY < entity->y + entity->height) ||
            (entity->y < bullet.upperY && bullet.upperY < entity->y + entity->height)) {
            if (entitiesBeingShot.empty()) {
                entitiesBeingShot.push_back(entity);
            } else {
                auto it = entitiesBeingShot.begin();
                for (; it != entitiesBeingShot.end(); ++it) {
                    if ((bullet.shootingLeft() && entity->x > (*it)->x) ||
                        (!bullet.shootingLeft() && entity->x < (*it)->x)) {
                        entitiesBeingShot.insert(it, entity);
                        break;
                    }
                }

                if (it == entitiesBeingShot.end()) {
                    entitiesBeingShot.push_back(entity);
                }
            }
        }
    }

    return entitiesBeingShot;
}
