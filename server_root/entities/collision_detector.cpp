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

bool CollisionDetector::checkForCollisions(Entity& entity, int deltaX, int deltaY, std::list<std::shared_ptr<Entity>>& entities) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameDimensions = config.getGameDimensions();
    int gameWidth = gameDimensions["GAME_WIDTH"];
    int gameHeight = gameDimensions["GAME_HEIGHT"];

    // Check for boundary collision
    if ((entity.x + deltaX) < 0 || (entity.x + deltaX + entity.width) > gameWidth ||
        (entity.y + deltaY) < 0 || (entity.y + deltaY + entity.height) > gameHeight) {
        return true;  // collision with boundary
    }

    for (auto& other : entities) {
        if (other->isDead())
            continue;
        if (&entity != other.get() && isColliding(entity, deltaX, deltaY, *other)) {
            return true;
        }
    }

    return false;
}

std::list<std::shared_ptr<Entity>> CollisionDetector::shoot(Attack& attack, std::list<std::shared_ptr<Entity>>& entities) {
    std::list<std::shared_ptr<Entity>> entitiesBeingATK;

    for (const auto& entity : entities) {
        // This is discarding for descarting units that are not in the direction of the bullet
        if ((entity->isDead() || attack.attackingLeft() && entity->x > attack.xOrigin) ||
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

std::shared_ptr<Player>& CollisionDetector::getPlayersInRange(int attackRange, Attack& attack, std::vector<std::shared_ptr<Player>>& players) {
    std::list<std::shared_ptr<Player>> playersInRange;

    for (const auto& player : players) {
        // This is discarding for descarting units that are not in the direction of the attack
        if ((player->isDead() || attack.attackingLeft() && player->x > attack.xOrigin) ||
            (attack.attackingRight() && player->x < attack.xOrigin)) {
            continue;
        }

        attackPlayers(attackRange, player, attack, playersInRange);
    }
    return playersInRange.front();
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
