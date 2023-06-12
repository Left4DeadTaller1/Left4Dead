#include "zombie.h"

#include "game_config.h"

Zombie::Zombie(int xPosition, int yPosition, std::string zombieId, ZombieType type)
    : Entity(xPosition, yPosition, zombieId), zombieType(type) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameParams = config.getGameParams();

    switch (zombieType) {
        case INFECTED:
            width = gameParams["INFECTED_WIDTH"];
            height = gameParams["INFECTED_HEIGHT"];
            break;
        case JUMPER:
            width = gameParams["JUMPER_WIDTH"];
            height = gameParams["JUMPER_HEIGHT"];
            break;

        case WITCH:
            width = gameParams["WITCH_WIDTH"];
            height = gameParams["WITCH_HEIGHT"];
            break;

        case SPEAR:
            width = gameParams["SPEAR_WIDTH"];
            height = gameParams["SPEAR_HEIGHT"];
            break;

        case VENOM:
            width = gameParams["VENOM_WIDTH"];
            height = gameParams["VENOM_HEIGHT"];
            break;
    }
}

// void Zombie::move() {
//     // TODO
// }

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
    dto->zombieType = this->getZombieType();
    return dto;
}

ZombieType Zombie::getZombieType() {
    return zombieType;
}

Attack Zombie::attack() {
    // TODO do a switch with the type of zombie to define the CD of atk, atk dmg and atk type
    atkCooldown = 10;
    int atkDmg = 10;
    AttackDirection attackDirection = LEFT;  // default value to avoid warnings
    int attackX = 0;

    switch (movementDirectionX) {
        case ENTITY_LEFT:
            attackDirection = LEFT;
            attackX = x;
            break;
        case ENTITY_RIGHT:
            attackDirection = RIGHT;
            attackX = x + width;
            break;
    }

    switch (zombieType) {
        case INFECTED:
            return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
            break;
        case JUMPER:
            return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
            break;

        case WITCH:
            // TODO: i think witchs don't attack
            return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
            break;

        case SPEAR:
            return Attack(SPEAR_ATTACK, atkDmg, attackX, attackDirection, y, y + height);
            break;

        case VENOM:
            // TODO: figure out later what attack it should do
            return Attack(SHORT_VENOM, atkDmg, attackX, attackDirection, y, y + height);
            break;

        default:
            return Attack(MELEE, 0, 0, RIGHT, 0, 0);
            break;
    }
}

Zombie::~Zombie() {
}