#include "witch.h"

#include <cmath>

#include "game_config.h"

Witch::Witch(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["WITCH_WIDTH"];
    height = entityParams["WITCH_HEIGHT"];
    health = entityParams["WITCH_HEALTH"];
    movementSpeed = entityParams["WITCH_SPEED"];
    // Todo: add jump ATk
    attacksCooldowns.insert(std::make_pair("melee", entityParams["WITCH_ATTACK_COOLDOWN"]));
}

std::shared_ptr<EntityDTO> Witch::getDto() {
    auto dto = std::dynamic_pointer_cast<ZombieDTO>(Zombie::getDto());
    dto->zombieType = WITCH;
    return dto;
}

int Witch::getAttackRange() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    return entityParams["WITCH_ATTACK_RANGE"];
}

Attack Witch::attack() {
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
    attacksCooldowns["melee"] = entityParams["WITCH_ATTACK_COOLDOWN"];
    atkDmg = entityParams["WITCH_ATTACK_DAMAGE"];
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
}

Witch::~Witch() {}