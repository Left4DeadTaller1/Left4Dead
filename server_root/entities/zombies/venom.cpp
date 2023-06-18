#include "venom.h"

#include <cmath>

#include "game_config.h"

Venom::Venom(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId), actionState(VENOM_IDLE) {
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
    auto venomDto = std::make_shared<VenomDTO>();

    // Fill in the base ZombieDTO parts
    fillBaseZombieDTO(venomDto);

    // Fill in the VenomDTO specific parts
    venomDto->zombieType = VENOM;
    venomDto->actionState = this->actionState;

    return venomDto;
}

int Venom::getAttackRange() {
    // TODO: change this to depending of atks cd
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
        actionState = VENOM_SHOOTING;
        return Attack(LONG_VENOM, atkDmg, attackX, attackDirection, y, y + height);
    } else {
        attacksCooldowns["spray"] = entityParams["VENOM_SPRAY_COOLDOWN"];
        atkDmg = entityParams["VENOM_SPRAY_DAMAGE"];
        actionState = VENOM_ATTACKING;
        return Attack(SHORT_VENOM, atkDmg, attackX, attackDirection, y, y + height);
    }
}

void Venom::startMoving() {
    actionState = VENOM_MOVING;
}

bool Venom::isMoving() {
    return actionState == VENOM_MOVING;
}

void Venom::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = VENOM_DYING;
        actionCounter = entityParams["VENOM_DYING_DURATION"];
    } else {
        actionState = VENOM_HURT;
        actionCounter = entityParams["VENOM_HURT_DURATION"];
    }
}

void Venom::checkIfDead() {
    if (actionState == VENOM_DYING && actionCounter == 0) {
        actionState = VENOM_DEAD;
    }
}

void Venom::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = VENOM_DEAD;
    actionCounter = entityParams["VENOM_DEATH_DURATION"];
}

bool Venom::isDead() {
    return actionState == VENOM_DEAD;
}

bool Venom::isRemovable() {
    return (actionCounter == 0 && actionState == VENOM_DEAD);
}

Venom::~Venom() {}