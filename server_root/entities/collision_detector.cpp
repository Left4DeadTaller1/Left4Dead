#include "collision_detector.h"

#include "game_config.h"

#define MELEE_RANGE 10
#define SPEAR_RANGE 15
#define SHORT_VENOM_RANGE 15
#define LONG_VENOM_RANGE 30

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
        return true;  // collision with another entity
    }

    return false;
}

bool CollisionDetector::checkForCollisions(Entity& entity, int deltaX, int deltaY, std::vector<std::shared_ptr<Entity>>& entities) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameParams = config.getGameParams();
    int gameWidth = gameParams["GAME_WIDTH"];
    int gameHeight = gameParams["GAME_HEIGHT"];

    // Check for boundary collision
    if ((entity.x + deltaX) < 0 || (entity.x + deltaX + entity.width) > gameWidth ||
        (entity.y + deltaY) < 0 || (entity.y + deltaY + entity.height) > gameHeight) {
        return true;  // collision with boundary
    }

    for (auto& other : entities) {
        if (&entity != other.get() && isColliding(entity, deltaX, deltaY, *other)) {
            return true;
        }
    }

    return false;
}

std::list<std::shared_ptr<Entity>> CollisionDetector::beingAttack(Attack& attack, std::vector<std::shared_ptr<Entity>>& entities) {
    std::list<std::shared_ptr<Entity>> entitiesBeingATK;

    for (const auto& entity : entities) {
        // This is discarding logic
        if ((attack.attackingLeft() && entity->x > attack.xOrigin) ||
            (attack.attackingRight() && entity->x < attack.xOrigin)) {
            continue;
        }

        // This is colision logic
        switch (attack.type) {
            case BULLET:
            case PIERCING_BULLET:
                beingAttackInfiniteRange(entity, attack, entitiesBeingATK);
                break;
            case MELEE:
                beingAttackFiniteRange(MELEE_RANGE, entity, attack, entitiesBeingATK);
                break;
            case SPEAR_ATTACK:
                beingAttackFiniteRange(SPEAR_RANGE, entity, attack, entitiesBeingATK);
                break;
            case SHORT_VENOM:
                beingAttackFiniteRange(SHORT_VENOM_RANGE, entity, attack, entitiesBeingATK);
                break;
            case LONG_VENOM:
                // TODO: maybe long venom is like a bullet
                beingAttackFiniteRange(LONG_VENOM_RANGE, entity, attack, entitiesBeingATK);
                break;
            default:
                break;
        }
    }

    return entitiesBeingATK;
}

void CollisionDetector::beingAttackInfiniteRange(const std::shared_ptr<Entity>& entity, Attack& attack, std::list<std::shared_ptr<Entity>>& entitiesBeingATK) {
    if ((entity->y < attack.lowerY && attack.lowerY < entity->y + entity->height) ||
        (entity->y < attack.upperY && attack.upperY < entity->y + entity->height)) {
        if (entitiesBeingATK.empty()) {
            entitiesBeingATK.push_back(entity);
        } else {
            auto it = entitiesBeingATK.begin();
            for (; it != entitiesBeingATK.end(); ++it) {
                if ((attack.attackingLeft() && entity->x > (*it)->x) ||
                    (attack.attackingRight() && entity->x < (*it)->x)) {
                    entitiesBeingATK.insert(it, entity);
                    break;
                }
            }

            if (it == entitiesBeingATK.end()) {
                entitiesBeingATK.push_back(entity);
            }
        }
    }
}

void CollisionDetector::beingAttackFiniteRange(int range, const std::shared_ptr<Entity>& entity, Attack& attack, std::list<std::shared_ptr<Entity>>& entitiesBeingATK) {
    if ((attack.lowerY < entity->y + entity->height && attack.upperY > entity->y) &&
        ((attack.attackingRight() && entity->x > attack.xOrigin && (entity->x - attack.xOrigin) < range) ||
         (attack.attackingLeft() && entity->x < attack.xOrigin && (attack.xOrigin - (entity->x + entity->width)) < range))) {
        if (entitiesBeingATK.empty()) {
            entitiesBeingATK.push_back(entity);
        } else {
            auto it = entitiesBeingATK.begin();
            for (; it != entitiesBeingATK.end(); ++it) {
                if ((attack.attackingLeft() && entity->x > (*it)->x) ||
                    (attack.attackingRight() && entity->x < (*it)->x)) {
                    entitiesBeingATK.insert(it, entity);
                    break;
                }
            }

            if (it == entitiesBeingATK.end()) {
                entitiesBeingATK.push_back(entity);
            }
        }
    }
}