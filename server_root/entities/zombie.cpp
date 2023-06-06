#include "zombie.h"

Zombie::Zombie(int xPosition, int yPosition, int width, int height, std::string zombieId)
    : Entity(xPosition, yPosition, width, height, zombieId), atkCooldown(0) {
}

void Zombie::move() {
    // TODO
}

std::string Zombie::getType() {
    return "zombie";
}

void Zombie::attack() {
    atkCooldown = ATK_COOLDOWN;
}

Zombie::~Zombie() {
}