#include "spear.h"

#include <cmath>

#include "game_config.h"

Spear::Spear(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId), actionState(SPEAR_IDLE) {
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
    auto spearDto = std::make_shared<SpearDTO>();

    // Fill in the base ZombieDTO parts
    fillBaseZombieDTO(spearDto);

    // Fill in the SpearDTO specific parts
    spearDto->zombieType = SPEAR;
    spearDto->actionState = this->actionState;

    return spearDto;
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

void Spear::startMoving() {
    actionState = SPEAR_MOVING;
}

bool Spear::isMoving() {
    return actionState == SPEAR_MOVING;
}

void Spear::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = SPEAR_DYING;
        actionCounter = 60;
    } else {
        actionState = SPEAR_HURT;
        actionCounter = 45;
    }
}

Spear::~Spear() {}