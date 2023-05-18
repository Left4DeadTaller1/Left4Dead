#include "zombie.h"

Zombie::Zombie(int xPosition, int yPosition, int width, int height)
    : Entity(xPosition, yPosition, width, height), atkCooldown(0) {
}

Zombie::~Zombie() {
}

void Zombie::attack() {
    atkCooldown = ATK_COOLDOWN;
}
