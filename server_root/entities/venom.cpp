#include "venom.h"

#include <cmath>

#include "game_config.h"

Venom::Venom(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["VENOM_WIDTH"];
    height = entityParams["VENOM_HEIGHT"];
    health = entityParams["VENOM_HEALTH"];
    movementSpeed = entityParams["VENOM_SPEED"];
    attacksCooldowns.insert(std::make_pair("spray", entityParams["VENOM_SPRAY_COOLDOWN"]));
    attacksCooldowns.insert(std::make_pair("proyectile", entityParams["VENOM_PROYECTILE_COOLDOWN"]));
}

std::shared_ptr<EntityDTO> Venom::getDto() {
    auto dto = std::dynamic_pointer_cast<ZombieDTO>(Zombie::getDto());
    dto->zombieType = VENOM;
    return dto;
}

int Venom::getAttackRange() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    return entityParams["VENOM_ATTACK_RANGE"];
}

Attack Venom::attack() {
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

    if (attacksCooldowns["proyectile"] == 0) {
        attacksCooldowns["proyectile"] = entityParams["VENOM_PROYECTILE_COOLDOWN"];
        atkDmg = entityParams["VENOM_PROYECTILE_DAMAGE"];
        return Attack(LONG_VENOM, atkDmg, attackX, attackDirection, y, y + height);
    } else {
        attacksCooldowns["spray"] = entityParams["VENOM_SPRAY_COOLDOWN"];
        atkDmg = entityParams["VENOM_SPRAY_DAMAGE"];
        return Attack(SHORT_VENOM, atkDmg, attackX, attackDirection, y, y + height);
    }
}

Venom::~Venom() {}