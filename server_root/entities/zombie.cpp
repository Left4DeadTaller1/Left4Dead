#include "zombie.h"

Zombie::Zombie(int xPosition, int yPosition, int width, int height, std::string zombieId)
    : Entity(xPosition, yPosition, width, height, zombieId) {
}

void Zombie::move() {
    // TODO
}

EntityType Zombie::getType() {
    return ZOMBIE;
}

bool Zombie::canAttack() {
    if (atkCooldown == 0) {
        return true;
    } else {
        return false;
    }
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
    dto->healthState = static_cast<int>(this->getHealthState());
    return dto;
}

Zombie::~Zombie() {
}