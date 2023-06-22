#include "zombie.h"

#include <cmath>

#include "game_config.h"

Zombie::Zombie(int xPosition, int yPosition, std::string zombieId, int mutationLevel)
    : Entity(xPosition, yPosition, zombieId), mutationLevel(mutationLevel) {}

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

void Zombie::fillBaseZombieDTO(std::shared_ptr<ZombieDTO> dto) {
    dto->type = ZOMBIE;
    dto->id = this->getId();
    dto->x = this->getX();
    dto->y = this->getY();
    dto->health = this->getHealth();
    dto->movementDirectionX = static_cast<int>(this->getMovementDirectionX());
    dto->facingDirection = this->facingDirection;
    dto->actionCounter = this->actionCounter;
}

void Zombie::decideTarget(std::vector<std::shared_ptr<Player>>& players) {
    if (players.empty()) {
        return;  // i mean you will never have 0 players but just in case
    }

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

    startMoving();
}

std::tuple<int, int> Zombie::getDirectionsAmount() {
    int xAmount = 0;
    int yAmount = 0;

    switch (movementDirectionX) {
        case ENTITY_LEFT:
            xAmount = -movementSpeed;
            break;

        case ENTITY_RIGHT:
            xAmount = movementSpeed;
            break;

        default:
            break;
    }

    switch (movementDirectionY) {
        case ENTITY_UP:
            yAmount = movementSpeed;
            break;

        case ENTITY_DOWN:
            yAmount = -movementSpeed;
            break;

        default:
            break;
    }

    return std::make_tuple(xAmount, yAmount);
}

void Zombie::decreaseATKCooldown() {
    for (auto& pair : attacksCooldowns) {
        pair.second -= 1;
    }
}

Zombie::~Zombie() {
}