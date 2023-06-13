#include "zombie.h"

#include "game_config.h"

Zombie::Zombie(int xPosition, int yPosition, std::string zombieId, ZombieType type)
    : Entity(xPosition, yPosition, zombieId), zombieType(type) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    switch (zombieType) {
        case INFECTED:
            width = entityParams["INFECTED_WIDTH"];
            height = entityParams["INFECTED_HEIGHT"];
            health = entityParams["INFECTED_HEALTH"];
            movementSpeed = entityParams["INFECTED_MOVEMENT_SPEED"];
            break;
        case JUMPER:
            width = entityParams["JUMPER_WIDTH"];
            height = entityParams["JUMPER_HEIGHT"];
            health = entityParams["JUMPER_HEALTH"];
            movementSpeed = entityParams["JUMPER_MOVEMENT_SPEED"];
            break;
        case WITCH:
            width = entityParams["WITCH_WIDTH"];
            height = entityParams["WITCH_HEIGHT"];
            health = entityParams["WITCH_HEALTH"];
            movementSpeed = entityParams["WITCH_MOVEMENT_SPEED"];
            break;
        case SPEAR:
            width = entityParams["SPEAR_WIDTH"];
            height = entityParams["SPEAR_HEIGHT"];
            health = entityParams["SPEAR_HEALTH"];
            movementSpeed = entityParams["SPEAR_MOVEMENT_SPEED"];
            break;
        case VENOM:
            width = entityParams["VENOM_WIDTH"];
            height = entityParams["VENOM_HEIGHT"];
            health = entityParams["VENOM_HEALTH"];
            movementSpeed = entityParams["VENOM_MOVEMENT_SPEED"];
            break;
        default:
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
        default:
            // TODO i think we should add a facing direction for zombies too
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
            // TODO: figure out later what attack it should do if range or melee venom
            return Attack(SHORT_VENOM, atkDmg, attackX, attackDirection, y, y + height);
            break;

        default:
            return Attack(MELEE, 0, 0, RIGHT, 0, 0);
            break;
    }
}

Zombie::~Zombie() {
}