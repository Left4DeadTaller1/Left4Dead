#include "zombie.h"

#include <cmath>

#include "game_config.h"

Zombie::Zombie(int xPosition, int yPosition, std::string zombieId)
    : Entity(xPosition, yPosition, zombieId) {}

EntityType Zombie::getType() {
    return ZOMBIE;
}

bool Zombie::canAttack() {
    for (const auto& pair : attacksCooldowns) {
        if (pair.second == 0) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<EntityDTO> Zombie::getDto() {
    auto dto = std::make_shared<ZombieDTO>();
    dto->type = ZOMBIE;
    dto->id = this->getId();
    dto->x = this->getX();
    dto->y = this->getY();
    dto->health = this->getHealth();
    dto->movementState = static_cast<int>(this->getMovementState());
    dto->movementDirectionX = static_cast<int>(this->getMovementDirectionX());
    dto->facingDirection = this->facingDirection;
    dto->healthState = static_cast<int>(this->getHealthState());
    return dto;
}

void Zombie::decideTarget(std::vector<std::shared_ptr<Player>>& players) {
    if (players.empty()) {
        return;  // i mean you will never have 0 players but just in case
    }

    movementState = ENTITY_RUNNING;

    int closestPlayerX = players[0]->getX();
    int closestPlayerY = players[0]->getY();
    int closestPlayerDistance = std::sqrt(std::pow((x - closestPlayerX), 2) + std::pow((y - closestPlayerY), 2));

    for (std::size_t i = 1; i < players.size(); i++) {
        int newDistance = std::sqrt(std::pow((x - players[i]->getX()), 2) + std::pow((y - players[i]->getY()), 2));
        if (newDistance < closestPlayerDistance) {
            closestPlayerX = players[i]->getX();
            closestPlayerY = players[i]->getY();
            closestPlayerDistance = newDistance;
        }
    }

    if (closestPlayerX < x) {
        movementDirectionX = ENTITY_LEFT;
        facingDirection = FACING_LEFT;
    } else {
        movementDirectionX = ENTITY_RIGHT;
        facingDirection = FACING_RIGHT;
    }

    if (closestPlayerY < y) {
        movementDirectionY = ENTITY_DOWN;
    } else {
        movementDirectionY = ENTITY_UP;
    }
}

void Zombie::decreaseATKCooldown() {
    for (auto& pair : attacksCooldowns) {
        pair.second -= 1;
    }
}

Zombie::~Zombie() {
}