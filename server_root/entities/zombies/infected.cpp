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
    health = entityParams["INFECTED_HEALTH"] + mutationIncrease;
    movementSpeed = entityParams["INFECTED_SPEED"] + mutationIncrease;
    attacksCooldowns.insert(std::make_pair("melee", entityParams["INFECTED_ATTACK_COOLDOWN"]));
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

int Infected::getAttackRange() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    return entityParams["INFECTED_ATTACK_RANGE"];
}

Attack Infected::attack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * spawnParams["MUTATION_STRENGTH"];

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
    atkDmg = entityParams["INFECTED_ATTACK_DAMAGE"] + mutationIncrease;
    actionState = INFECTED_ATTACKING;
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
}

void Infected::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = INFECTED_DYING;
        actionCounter = entityParams["INFECTED_DYING_DURATION"];
    } else {
        actionState = INFECTED_HURT;
        actionCounter = entityParams["INFECTED_HURT_DURATION"];
    }
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