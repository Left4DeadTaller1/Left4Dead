#include "witch.h"

#include <cmath>

#include "game_config.h"

Witch::Witch(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId), actionState(WITCH_IDLE) {
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
    auto witchDto = std::make_shared<WitchDTO>();

    // Fill in the base ZombieDTO parts
    fillBaseZombieDTO(witchDto);

    // Fill in the WitchDTO specific parts
    witchDto->zombieType = WITCH;
    witchDto->actionState = this->actionState;

    return witchDto;
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
    actionState = WITCH_ATTACKING;
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
}

void Witch::startMoving() {
    actionState = WITCH_MOVING;
}

bool Witch::isMoving() {
    return actionState == WITCH_MOVING;
}

void Witch::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = WITCH_DYING;
        actionCounter = entityParams["WITCH_DYING_DURATION"];
    } else {
        actionState = WITCH_HURT;
        actionCounter = entityParams["WITCH_HURT_DURATION"];
    }
}

void Witch::checkIfDead() {
    if (actionState == WITCH_DYING && actionCounter == 0) {
        kill();
    }
}

void Witch::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = WITCH_DYING;
    actionCounter = entityParams["WITCH_DEATH_DURATION"];
}

bool Witch::isDead() {
    return actionState == WITCH_DEAD;
}

bool Witch::isRemovable() {
    return actionState == WITCH_DYING && actionCounter == 0;
}

Witch::~Witch() {}