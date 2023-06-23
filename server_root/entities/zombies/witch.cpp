#include "witch.h"

#include <cmath>
#include <iostream>

#include "game_config.h"

Witch::Witch(int xPosition, int yPosition, std::string zombieId, int mutationLevel)
    : Zombie(xPosition, yPosition, zombieId, mutationLevel), actionState(WITCH_IDLE) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * spawnParams["MUTATION_STRENGTH"];

    width = entityParams["WITCH_WIDTH"];
    height = entityParams["WITCH_HEIGHT"];
    health = entityParams["WITCH_HEALTH"] + mutationIncrease;
    movementSpeed = entityParams["WITCH_SPEED"] + mutationIncrease;
    // Todo: add jump ATk
    attacksCooldowns.insert(std::make_pair("melee", entityParams["WITCH_ATTACK_COOLDOWN"]));
    attacksCooldowns.insert(std::make_pair("wail", entityParams["WITCH_WAIL_COOLDOWN"]));
}

std::shared_ptr<EntityDTO> Witch::getDto() {
    auto witchDto = std::make_shared<WitchDTO>();

    // Fill in the base ZombieDTO parts
    fillBaseZombieDTO(witchDto);

    // Fill in the WitchDTO specific parts
    witchDto->zombieType = WITCH;
    std::cout << "Action state before DTO: " << actionState << std::endl;
    witchDto->actionState = this->actionState;

    return witchDto;
}

// int Witch::getAttackRange() {
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     return entityParams["WITCH_ATTACK_RANGE"];
// }

std::shared_ptr<Ability> Witch::useSkill() {
    if (attacksCooldowns["wail"] != 0) {
        std::shared_ptr<Ability> noneAbility = std::make_shared<Ability>();
        noneAbility->type = INVALID;
        return noneAbility;
    }
    std::cout << "witch using wail" << std::endl;

    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    attacksCooldowns["wail"] = entityParams["WITCH_WAIL_COOLDOWN"];
    actionState = WITCH_SHOUTING;
    actionCounter = entityParams["WITCH_WAIL_DURATION"];
    std::shared_ptr<Wail> wailAbility = std::make_shared<Wail>();
    wailAbility->WitchX = x;
    wailAbility->WitchY = y;
    wailAbility->witchInfectionLevel = mutationLevel;
    return wailAbility;
}

Attack Witch::attack() {
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
    attacksCooldowns["melee"] = entityParams["WITCH_ATTACK_COOLDOWN"];
    atkDmg = entityParams["WITCH_ATTACK_DAMAGE"] + mutationIncrease;
    actionState = WITCH_ATTACKING;
    int attackRange = entityParams["WITCH_ATTACK_RANGE"];
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height, attackRange);
}

void Witch::startMoving() {
    actionState = WITCH_MOVING;
}

bool Witch::isMoving() {
    return actionState == WITCH_MOVING;
}

void Witch::idle() {
    actionState = WITCH_IDLE;
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

bool Witch::checkIfDead() {
    if (actionState == WITCH_DYING && actionCounter == 0) {
        return true;
    }
    return false;
}

void Witch::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = WITCH_DYING;
    actionCounter = entityParams["WITCH_DEATH_DURATION"];
}

bool Witch::isDead() {
    return (actionState == WITCH_DEAD && actionCounter == WITCH_DYING);
}

bool Witch::isRemovable() {
    return actionState == WITCH_DYING && actionCounter == 0;
}

Witch::~Witch() {}

void Witch::setActionState(WitchActionState actionState) {
    this->actionState = actionState;
}

WitchActionState Witch::getActionState() {
    return actionState;
}