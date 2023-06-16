#include "spear.h"

#include <cmath>

#include "game_config.h"

Spear::Spear(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["SPEAR_WIDTH"];
    height = entityParams["SPEAR_HEIGHT"];
    health = entityParams["SPEAR_HEALTH"];
    movementSpeed = entityParams["SPEAR_SPEED"];
    // Todo: add jump ATk
    attacksCooldowns.insert(std::make_pair("melee", entityParams["SPEAR_ATTACK_COOLDOWN"]));
}

std::shared_ptr<EntityDTO> Spear::getDto() {
    auto dto = std::dynamic_pointer_cast<ZombieDTO>(Zombie::getDto());
    dto->zombieType = SPEAR;
    return dto;
}

int Spear::getAttackRange() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    return entityParams["SPEAR_ATTACK_RANGE"];
}

Attack Spear::attack() {
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
    attacksCooldowns["melee"] = entityParams["SPEAR_ATTACK_COOLDOWN"];
    atkDmg = entityParams["SPEAR_ATTACK_DAMAGE"];
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
}

Spear::~Spear() {}