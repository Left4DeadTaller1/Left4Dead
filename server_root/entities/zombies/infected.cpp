#include "infected.h"

#include <cmath>

#include "game_config.h"

Infected::Infected(int xPosition, int yPosition, std::string zombieId, int mutationLevel)
    : Zombie(xPosition, yPosition, zombieId, mutationLevel), actionState(INFECTED_IDLE) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * spawnParams["MUTATION_STRENGTH"];

    width = entityParams["INFECTED_WIDTH"];
    height = entityParams["INFECTED_HEIGHT"];
    health = entityParams["INFECTED_HEALTH"] * (1 * (1 + mutationIncrease));
    movementSpeed = entityParams["INFECTED_SPEED"] * (1 * (1 + mutationIncrease));
    attacksCooldowns.insert(std::make_pair("melee", 0));
}

std::shared_ptr<EntityDTO> Infected::getDto() {
    auto infectedDto = std::make_shared<InfectedDTO>();

    // Fill in the base ZombieDTO parts
    fillBaseZombieDTO(infectedDto);

    // Fill in the InfectedDTO specific parts
    infectedDto->zombieType = INFECTED;
    infectedDto->actionState = this->actionState;

    return infectedDto;
}

// int Infected::getAttackRange() {
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     return entityParams["INFECTED_ATTACK_RANGE"];
// }

Attack Infected::generateAttack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * spawnParams["MUTATION_STRENGTH"];

    int atkDmg = entityParams["INFECTED_ATTACK_DAMAGE"] * (1 * (1 + mutationIncrease));
    int attackRange = entityParams["INFECTED_ATTACK_RANGE"];
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

void Infected::attackPlayer() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    attacksCooldowns["melee"] = entityParams["INFECTED_ATTACK_COOLDOWN"];
    actionState = INFECTED_ATTACKING;
}

bool Infected::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = INFECTED_DYING;
        actionCounter = entityParams["INFECTED_DYING_DURATION"];
        return true;
    } else {
        actionState = INFECTED_HURT;
        actionCounter = entityParams["INFECTED_HURT_DURATION"];
        return false;
    }
    return false;
}

void Infected::startMoving() {
    actionState = INFECTED_MOVING;
}

void Infected::idle() {
    actionState = INFECTED_IDLE;
}

bool Infected::isMoving() {
    return actionState == INFECTED_MOVING;
}

bool Infected::checkIfDead() {
    if (actionState == INFECTED_DYING && actionCounter == 0) {
        return true;
    }
    return false;
}

void Infected::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = INFECTED_DEAD;
    actionCounter = entityParams["INFECTED_DEATH_DURATION"];
}

bool Infected::isRemovable() {
    return (actionCounter == 0 && actionState == INFECTED_DEAD);
}

bool Infected::isDead() {
    return (actionState == INFECTED_DEAD || actionState == INFECTED_DYING);
}

Infected::~Infected() {}