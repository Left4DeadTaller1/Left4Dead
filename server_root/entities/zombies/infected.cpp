#include "infected.h"

#include <cmath>

#include "game_config.h"

Infected::Infected(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId), actionState(INFECTED_IDLE) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();

    width = entityParams["INFECTED_WIDTH"];
    height = entityParams["INFECTED_HEIGHT"];
    health = entityParams["INFECTED_HEALTH"];
    movementSpeed = entityParams["INFECTED_SPEED"];
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
    atkDmg = entityParams["INFECTED_ATTACK_DAMAGE"];
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height);
}

void Infected::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = INFECTED_DYING;
        actionCounter = 60;
    } else {
        actionState = INFECTED_HURT;
        actionCounter = 45;
    }
}

void Infected::startMoving() {
    actionState = INFECTED_MOVING;
}

bool Infected::isMoving() {
    return actionState == INFECTED_MOVING;
}

Infected::~Infected() {}