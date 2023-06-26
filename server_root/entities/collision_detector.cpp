#include "collision_detector.h"

#include "game_config.h"

// #define MELEE_RANGE 10
// #define SPEAR_RANGE 15
// #define SHORT_VENOM_RANGE 15
// #define LONG_VENOM_RANGE 30

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

std::list<std::shared_ptr<Entity>> collidesWhileJumping(Zombie& jumper, int deltaX, int deltaY, std::list<std::shared_ptr<Entity>>& entities) {
    std::list<std::shared_ptr<Entity>> entitiesBeingCrashed;

    for (const auto& entity : entities) {
        if (isColliding(jumper, deltaX, deltaY, entity)) {
            if (entitiesBeingCrashed.empty()) {
                entitiesBeingCrashed.push_back(entity);
            } else {
                auto it = entitiesBeingCrashed.begin();
                for (; it != entitiesBeingCrashed.end(); ++it) {
                    if ((jumper.facingLeft() && entity->x > (*it)->x) ||
                        (jumper.facingRight() && entity->x < (*it)->x)) {
                        entitiesBeingCrashed.insert(it, entity);
                        break;
                    }
                }
                if (it == entitiesBeingCrashed.end()) {
                    entitiesBeingCrashed.push_back(entity);
                }
            }
        }
    }

    return entitiesBeingCrashed.front();
}

//

bool CollisionDetector::isColliding(Entity& entity, int targetX, int targetY) {
    // TODO WE SHOULD ALSO CHECK GAME BOUDNARIeS
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> infectedDimensions = config.getEntitiesParams();
    int infectedWidth = infectedDimensions["INFECTED_WIDTH"];
    int infectedHeight = infectedDimensions["INFECTED_HEIGHT"];

    if ((entity.x + entity.width) < targetX || (entity.x) > targetX + infectedWidth) {
        return false;
    }

    if ((entity.y) + entity.width < targetY || (entity.y) > targetY + infectedHeight) {
        return false;
    }

    // TODO: i think this is not needed and is overkill
    if (targetX + infectedWidth >= entity.x && targetX <= entity.x + entity.width &&
        targetY + infectedHeight >= entity.y && targetY <= entity.y + entity.height) {
        return true;  // collision with another entity
    }
    return true;
}

bool CollisionDetector::isEmptySpace(std::list<std::shared_ptr<Entity>>& entities, int x, int y) {
    for (auto& entity : entities) {
        if (!isColliding(*entity, x, y))
            return true;
    }
    return false;
}

bool CollisionDetector::willCollideHorizontally(Entity& e1, Entity& e2) {
    // discard cuz they are not in the same "depth"
    if ((e1.y) + e1.height < e2.y || (e1.y) > e2.y + e2.height)
        return false;

    return true;
}

bool CollisionDetector::willCollideVertically(Entity& e1, Entity& e2) {
    // discard cuz they are not in the same "depth"
    if ((e1.x) + e1.width < e2.x || (e1.x > e2.x + e2.width))
        return false;

    return true;
}

std::tuple<int, int> CollisionDetector::checkForCollisions(Entity& entity, int deltaX, int deltaY, std::list<std::shared_ptr<Entity>>& entities) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameDimensions = config.getGameDimensions();
    int gameWidth = gameDimensions["GAME_WIDTH"];
    int gameHeight = gameDimensions["GAME_HEIGHT"];

    int maxMoveX = entity.getMovementDirectionX() == ENTITY_LEFT ? entity.x : gameWidth - (entity.x + entity.width);
    int maxMoveY = entity.getMovementDirectionY() == ENTITY_DOWN ? entity.y : gameHeight - (entity.y + entity.height);

    for (auto& other : entities) {
        if (other->isDead() || &entity == other.get())
            continue;

        if (willCollideHorizontally(entity, *other)) {
            if (entity.getMovementDirectionX() == ENTITY_LEFT) {
                int distance = entity.x - (other->x + other->width);
                if (distance >= 0 && distance < maxMoveX)
                    maxMoveX = distance;
            } else if (entity.getMovementDirectionX() == ENTITY_RIGHT) {
                int distance = other->x - (entity.x + entity.width);
                if (distance >= 0 && distance < maxMoveX)
                    maxMoveX = distance;
            }
        }

        if (willCollideVertically(entity, *other)) {
            if (entity.getMovementDirectionY() == ENTITY_UP) {
                int distance = other->y - (entity.y + entity.height);
                if (distance >= 0 && distance < maxMoveY)
                    maxMoveY = distance;
            } else if (entity.getMovementDirectionY() == ENTITY_DOWN) {
                int distance = entity.y - (other->y + other->height);
                if (distance >= 0 && distance < maxMoveY)
                    maxMoveY = distance;
            }
        }
    }

    int actualMovementX = std::min(maxMoveX, abs(deltaX)) * (deltaX < 0 ? -1 : 1);
    int actualMovementY = std::min(maxMoveY, abs(deltaY)) * (deltaY < 0 ? -1 : 1);

    return std::make_tuple(actualMovementX, actualMovementY);
}

std::list<std::shared_ptr<Entity>> CollisionDetector::shoot(Attack& attack, std::list<std::shared_ptr<Entity>>& entities) {
    std::list<std::shared_ptr<Entity>> entitiesBeingATK;

    for (const auto& entity : entities) {
        // This is discarding for descarting units that are not in the direction of the bullet
        if (entity->isDead() ||
            (attack.attackingLeft() && entity->x > attack.xOrigin) ||
            (attack.attackingRight() && entity->x < attack.xOrigin)) {
            continue;
        }

        shootZombie(entity, attack, entitiesBeingATK);
    }

    return entitiesBeingATK;
}

void CollisionDetector::shootZombie(const std::shared_ptr<Entity>& entity, Attack& attack, std::list<std::shared_ptr<Entity>>& entitiesBeingATK) {
    if (entity->getType() == PLAYER)
        return;

    if ((attack.lowerY <= entity->y && entity->y <= attack.upperY) ||
        (attack.lowerY <= entity->y + entity->height && entity->y + entity->height <= attack.upperY) ||
        (attack.lowerY <= entity->y && entity->y + entity->height <= attack.upperY)) {
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

std::shared_ptr<Player> CollisionDetector::getPlayersInRange(int attackRange, Attack& attack, std::vector<std::shared_ptr<Player>>& players) {
    std::list<std::shared_ptr<Player>> playersInRange;

    for (const auto& player : players) {
        if (player->isDead() ||
            (attack.attackingLeft() && player->x > attack.xOrigin) ||
            (attack.attackingRight() && player->x < attack.xOrigin)) {
            continue;
        }

        attackPlayers(attackRange, player, attack, playersInRange);
    }

    if (!playersInRange.empty()) {
        return playersInRange.front();
    } else {
        return std::shared_ptr<Player>();
    }
}

void CollisionDetector::attackPlayers(int range, const std::shared_ptr<Player>& player, Attack& attack, std::list<std::shared_ptr<Player>>& playersInRange) {
    bool isInRange = false;

    // I check first that the attack and the player are in the same Depth (withing the Y values)
    if (attack.lowerY < (player->y + player->height) && attack.upperY > player->y) {
        // And now we check that the player is in the range of the attack in X
        if (attack.attackingRight() && (player->x - attack.xOrigin) < range)
            isInRange = true;
        else if (attack.attackingLeft() && (attack.xOrigin - (player->x + player->width)) < range)
            isInRange = true;
    }

    if (isInRange) {
        if (playersInRange.empty()) {
            playersInRange.push_back(player);
        } else {
            auto it = playersInRange.begin();
            for (; it != playersInRange.end(); ++it) {
                if ((attack.attackingLeft() && player->x > (*it)->x) ||
                    (attack.attackingRight() && player->x < (*it)->x)) {
                    playersInRange.insert(it, player);
                    break;
                }
            }

            if (it == playersInRange.end()) {
                playersInRange.push_back(player);
            }
        }
    }
}
