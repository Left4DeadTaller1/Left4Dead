#include "venom.h"

#include <cmath>

#include "game_config.h"

Venom::Venom(int xPosition, int yPosition, std::string zombieId, int mutationLevel)
    : Zombie(xPosition, yPosition, zombieId, mutationLevel), actionState(VENOM_IDLE) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * spawnParams["MUTATION_STRENGTH"];

    width = entityParams["VENOM_WIDTH"];
    height = entityParams["VENOM_HEIGHT"];
    health = entityParams["VENOM_HEALTH"] * (1 + mutationIncrease);
    movementSpeed = entityParams["VENOM_SPEED"] * (1 + mutationIncrease);
    attacksCooldowns.insert(std::make_pair("spray", 0));
    attacksCooldowns.insert(std::make_pair("proyectile", 0));
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

// int Venom::getAttackRange() {
//     // TODO: change this to depending of atks cd
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     return entityParams["VENOM_ATTACK_RANGE"];
// }

Attack Venom::generateAttack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * spawnParams["MUTATION_STRENGTH"];
    int atkDmg;
    int attackRange;
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
        atkDmg = entityParams["VENOM_PROYECTILE_DAMAGE"] * (1 + mutationIncrease);
        attackRange = entityParams["VENOM_PROYECTILE_RANGE"];
        return Attack(LONG_VENOM, atkDmg, attackX, attackDirection, y, y + height, attackRange);
    } else {
        atkDmg = entityParams["VENOM_SPRAY_DAMAGE"] * (1 + mutationIncrease);
        attackRange = entityParams["VENOM_SPRAY_RANGE"];
        return Attack(SHORT_VENOM, atkDmg, attackX, attackDirection, y, y + height, attackRange);
    }
}

void Venom::attackPlayer() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    if (attacksCooldowns["proyectile"] == 0) {
        attacksCooldowns["proyectile"] = entityParams["VENOM_PROYECTILE_COOLDOWN"];
        actionState = VENOM_SHOOTING;
    } else {
        attacksCooldowns["spray"] = entityParams["VENOM_SPRAY_COOLDOWN"];
        actionState = VENOM_ATTACKING;
    }
}

void Venom::startMoving() {
    actionState = VENOM_MOVING;
}

bool Venom::isMoving() {
    return actionState == VENOM_MOVING;
}

void Venom::idle() {
    actionState = VENOM_IDLE;
}

bool Venom::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = VENOM_DYING;
        actionCounter = entityParams["VENOM_DYING_DURATION"];
        return true;
    } else {
        actionState = VENOM_HURT;
        actionCounter = entityParams["VENOM_HURT_DURATION"];
        return false;
    }
    return true;
}

bool Venom::checkIfDead() {
    if (actionState == VENOM_DYING && actionCounter == 0) {
        return true;
    }
    return false;
}

void Venom::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = VENOM_DEAD;
    actionCounter = entityParams["VENOM_DEATH_DURATION"];
}

bool Venom::isDead() {
    return (actionState == VENOM_DEAD || actionState == VENOM_DYING);
}

bool Venom::isRemovable() {
    return (actionCounter == 0 && actionState == VENOM_DEAD);
}

Venom::~Venom() {}