#include "infected.h"

#include <cmath>

#include "game_config.h"

Infected::Infected(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["INFECTED_WIDTH"];
    height = entityParams["INFECTED_HEIGHT"];
    health = entityParams["INFECTED_HEALTH"];
    movementSpeed = entityParams["INFECTED_SPEED"];
    attacksCooldowns.insert(std::make_pair("melee", entityParams["INFECTED_ATTACK_COOLDOWN"]));
}

std::shared_ptr<EntityDTO> Infected::getDto() {
    auto dto = std::dynamic_pointer_cast<ZombieDTO>(Zombie::getDto());
    dto->zombieType = INFECTED;
    return dto;
}

int Infected::getAttackRange() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    return entityParams["INFECTED_ATTACK_RANGE"];
}

Attack Infected::attack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    int atkDmg;
    AttackDirection attackDirection = LEFT;  // default value to avoid warnings
    int attackX = 0;

    switch (facingDirection) {
        case FACING_LEFT:
            attackDirection = LEFT;
            attackX = x;
            break;
        case FACING_RIGHT:
            attackDirection = RIGHT;
            attackX = x + width;
            break;
    }
    attacksCooldowns["melee"] = entityParams["INFECTED_ATTACK_COOLDOWN"];
    atkDmg = entityParams["INFECTED_ATTACK_DAMAGE"];
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
}

Infected::~Infected() {}