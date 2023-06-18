#include "jumper.h"

#include <cmath>

#include "game_config.h"

Jumper::Jumper(int xPosition, int yPosition, std::string zombieId)
    : Zombie(xPosition, yPosition, zombieId), actionState(JUMPER_IDLE) {
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
    auto jumperDto = std::make_shared<JumperDTO>();

    // Fill in the base ZombieDTO parts
    fillBaseZombieDTO(jumperDto);

    // Fill in the JumperDTO specific parts
    jumperDto->zombieType = JUMPER;
    jumperDto->actionState = this->actionState;

    return jumperDto;
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

void Jumper::startMoving() {
    actionState = JUMPER_MOVING;
}

bool Jumper::isMoving() {
    return actionState == JUMPER_MOVING;
}

void Jumper::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = JUMPER_DYING;
        actionCounter = entityParams["JUMPER_DEATH_DURATION"];
    } else {
        actionState = JUMPER_HURT;
        actionCounter = entityParams["JUMPER_HURT_DURATION"];
    }
}

Jumper::~Jumper() {}