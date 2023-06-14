#include "zombie.h"

#include <cmath>

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
            movementSpeed = entityParams["INFECTED_SPEED"];
            attacksCooldowns.insert(std::make_pair("melee", entityParams["INFECTED_ATTACK_COOLDOWN"]));
            break;
        case JUMPER:
            width = entityParams["JUMPER_WIDTH"];
            height = entityParams["JUMPER_HEIGHT"];
            health = entityParams["JUMPER_HEALTH"];
            movementSpeed = entityParams["JUMPER_SPEED"];
            attacksCooldowns.insert(std::make_pair("melee", entityParams["JUMPER_ATTACK_COOLDOWN"]));
            break;
        case WITCH:
            width = entityParams["WITCH_WIDTH"];
            height = entityParams["WITCH_HEIGHT"];
            health = entityParams["WITCH_HEALTH"];
            movementSpeed = entityParams["WITCH_SPEED"];
            attacksCooldowns.insert(std::make_pair("melee", entityParams["WITCH_ATTACK_COOLDOWN"]));
            break;
        case SPEAR:
            width = entityParams["SPEAR_WIDTH"];
            height = entityParams["SPEAR_HEIGHT"];
            health = entityParams["SPEAR_HEALTH"];
            movementSpeed = entityParams["SPEAR_SPEED"];
            attacksCooldowns.insert(std::make_pair("melee", entityParams["SPEAR_ATTACK_COOLDOWN"]));
            break;
        case VENOM:
            width = entityParams["VENOM_WIDTH"];
            height = entityParams["VENOM_HEIGHT"];
            health = entityParams["VENOM_HEALTH"];
            movementSpeed = entityParams["VENOM_SPEED"];
            attacksCooldowns.insert(std::make_pair("spray", entityParams["VENOM_SPRAY_COOLDOWN"]));
            attacksCooldowns.insert(std::make_pair("proyectile", entityParams["VENOM_PROYECTILE_COOLDOWN"]));
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
    switch (zombieType) {
        case INFECTED:
        case JUMPER:
        case WITCH:
        case SPEAR:
            if (attacksCooldowns["melee"] == 0) {
                return true;
            } else {
                return false;
            }
            break;
        case VENOM:
            if (attacksCooldowns["proyectile"] == 0 || attacksCooldowns["spray"] == 0) {
                return true;
            } else {
                return false;
            }
            break;

        default:
            return false;
            break;
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
    } else {
        movementDirectionX = ENTITY_RIGHT;
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

int Zombie::getAttackRange() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    switch (zombieType) {
        case INFECTED:
            return entityParams["INFECTED_ATTACK_RANGE"];
            break;

        case JUMPER:
            return entityParams["JUMPER_ATTACK_RANGE"];
            break;

        case WITCH:
            return entityParams["WITCH_ATTACK_RANGE"];
            break;

        case SPEAR:
            return entityParams["SPEAR_ATTACK_RANGE"];
            break;

        case VENOM:
            if (attacksCooldowns["proyectile"] == 0) {
                return entityParams["VENOM_PROYECTILE_RANGE"];
            } else {
                return entityParams["VENOM_SPRAY_RANGE"];
            }
            break;
        default:
            return 0;
            break;
    }
}

Attack Zombie::attack() {
    // TODO do a switch with the type of zombie to define the CD of atk, atk dmg and atk type
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    int atkDmg;
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
            attacksCooldowns["melee"] = entityParams["INFECTED_ATTACK_COOLDOWN"];
            atkDmg = entityParams["INFECTED_ATTACK_DAMAGE"];
            return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
            break;

        case JUMPER:
            attacksCooldowns["melee"] = entityParams["JUMPER_ATTACK_COOLDOWN"];
            atkDmg = entityParams["JUMPER_ATTACK_DAMAGE"];
            return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
            break;

        case WITCH:
            // TODO: i think witchs don't attack
            attacksCooldowns["melee"] = entityParams["WITCH_ATTACK_COOLDOWN"];
            atkDmg = entityParams["WITCH_ATTACK_DAMAGE"];
            return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
            break;

        case SPEAR:
            attacksCooldowns["melee"] = entityParams["SPEAR_ATTACK_COOLDOWN"];
            atkDmg = entityParams["SPEAR_ATTACK_DAMAGE"];
            return Attack(SPEAR_ATTACK, atkDmg, attackX, attackDirection, y, y + height);
            break;

        case VENOM:
            if (attacksCooldowns["proyectile"] == 0) {
                attacksCooldowns["proyectile"] = entityParams["VENOM_PROYECTILE_COOLDOWN"];
                atkDmg = entityParams["VENOM_PROYECTILE_DAMAGE"];
                return Attack(LONG_VENOM, atkDmg, attackX, attackDirection, y, y + height);
            } else {
                attacksCooldowns["spray"] = entityParams["VENOM_SPRAY_COOLDOWN"];
                atkDmg = entityParams["VENOM_SPRAY_DAMAGE"];
                return Attack(SHORT_VENOM, atkDmg, attackX, attackDirection, y, y + height);
            }
            break;

        default:
            return Attack(MELEE, 0, 0, RIGHT, 0, 0);
            break;
    }
}

Zombie::~Zombie() {
}