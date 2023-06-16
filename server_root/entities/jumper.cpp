#include "jumper.h"

#include <cmath>

#include "game_config.h"

Jumper::Jumper(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["JUMPER_WIDTH"];
    height = entityParams["JUMPER_HEIGHT"];
    health = entityParams["JUMPER_HEALTH"];
    movementSpeed = entityParams["JUMPER_SPEED"];
    // Todo: add jump ATk
    attacksCooldowns.insert(std::make_pair("melee", entityParams["JUMPER_ATTACK_COOLDOWN"]));
}

std::shared_ptr<EntityDTO> Jumper::getDto() {
    auto dto = std::dynamic_pointer_cast<ZombieDTO>(Zombie::getDto());
    dto->zombieType = JUMPER;
    return dto;
}

int Jumper::getAttackRange() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    return entityParams["JUMPER_ATTACK_RANGE"];
}

Attack Jumper::attack() {
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
    attacksCooldowns["melee"] = entityParams["JUMPER_ATTACK_COOLDOWN"];
    atkDmg = entityParams["JUMPER_ATTACK_DAMAGE"];
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
}

Jumper::~Jumper() {}