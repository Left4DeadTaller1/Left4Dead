#include "spear.h"

#include <cmath>

#include "game_config.h"

Spear::Spear(int xPosition, int yPosition, std::string zombieId, int mutationLevel)
    : Zombie(xPosition, yPosition, zombieId, mutationLevel), actionState(SPEAR_IDLE) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * (spawnParams["MUTATION_STRENGTH"] / 10);
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["SPEAR_WIDTH"];
    height = entityParams["SPEAR_HEIGHT"];
    health = entityParams["SPEAR_HEALTH"] * (1 + mutationIncrease);
    movementSpeed = entityParams["SPEAR_SPEED"] * (1 + mutationIncrease);
    // Todo: add jump ATk
    attacksCooldowns.insert(std::make_pair("melee", 0));
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

// int Spear::getAttackRange() {
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     return entityParams["SPEAR_ATTACK_RANGE"];
// }

Attack Spear::generateAttack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * (spawnParams["MUTATION_STRENGTH"] / 10);
    int atkDmg = entityParams["SPEAR_ATTACK_DAMAGE"] * (1 + mutationIncrease);
    int attackRange = entityParams["SPEAR_ATTACK_RANGE"];
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

    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height, attackRange);
}

void Spear::attackPlayer() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    attacksCooldowns["melee"] = entityParams["SPEAR_ATTACK_COOLDOWN"];
    actionState = SPEAR_ATTACKING;
}

void Spear::startMoving() {
    actionState = SPEAR_MOVING;
}

bool Spear::isMoving() {
    return actionState == SPEAR_MOVING;
}

void Spear::idle() {
    actionState = SPEAR_IDLE;
}

bool Spear::takeDamage(int damage) {
    if (damage <= 0)
        return false;
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = SPEAR_DYING;
        actionCounter = entityParams["SPEAR_DYING_DURATION"];
        return true;
    } else {
        actionState = SPEAR_HURT;
        actionCounter = entityParams["SPEAR_HURT_DURATION"];
        return false;
    }
    return false;
}

bool Spear::checkIfDead() {
    if (actionState == SPEAR_DYING && actionCounter == 0) {
        return true;
    }
    return false;
}

void Spear::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = SPEAR_DEAD;
    actionCounter = entityParams["SPEAR_DEATH_DURATION"];
}

bool Spear::isDead() {
    return (actionState == SPEAR_DEAD || actionState == SPEAR_DYING);
}

bool Spear::isRemovable() {
    return (actionCounter == 0 && actionState == SPEAR_DEAD);
}

Spear::~Spear() {}