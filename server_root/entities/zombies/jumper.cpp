#include "jumper.h"

#include <cmath>

#include "game_config.h"

Jumper::Jumper(int xPosition, int yPosition, std::string zombieId, int mutationLevel)
    : Zombie(xPosition, yPosition, zombieId, mutationLevel), actionState(JUMPER_IDLE) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * spawnParams["MUTATION_STRENGTH"];

    width = entityParams["JUMPER_WIDTH"];
    height = entityParams["JUMPER_HEIGHT"];
    health = entityParams["JUMPER_HEALTH"] + mutationIncrease;
    movementSpeed = entityParams["JUMPER_SPEED"] + mutationIncrease;
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

// int Jumper::getAttackRange() {
//     GameConfig& config = GameConfig::getInstance();
//     std::map<std::string, int> entityParams = config.getEntitiesParams();
//     return entityParams["JUMPER_ATTACK_RANGE"];
// }

Attack Jumper::attack() {
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
    attacksCooldowns["melee"] = entityParams["JUMPER_ATTACK_COOLDOWN"];
    atkDmg = entityParams["JUMPER_ATTACK_DAMAGE"] + mutationIncrease;
    actionState = JUMPER_ATTACKING;
    int attackRange = entityParams["JUMPER_ATTACK_RANGE"];
    return Attack(MELEE, atkDmg, attackX, attackDirection, y, y + height, attackRange);
}

void Jumper::startMoving() {
    actionState = JUMPER_MOVING;
}

void Jumper::idle() {
    actionState = JUMPER_IDLE;
}

bool Jumper::isMoving() {
    return actionState == JUMPER_MOVING;
}

void Jumper::takeDamage(int damage) {
    std::cout << "Jumper taking damage: " << damage << std::endl;
    std::cout << "Health: " << health << std::endl;

    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        std::cout << "Jumper Dying, health: " << health << std::endl;
        actionState = JUMPER_DYING;
        actionCounter = entityParams["JUMPER_DYING_DURATION"];
    } else {
        actionState = JUMPER_HURT;
        actionCounter = entityParams["JUMPER_HURT_DURATION"];
    }

    std::cout << "Health after dmg: " << health << std::endl
              << std::endl;
}

bool Jumper::checkIfDead() {
    if (actionState == JUMPER_DYING && actionCounter == 0) {
        return true;
    }
    return false;
}

void Jumper::kill() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    actionState = JUMPER_DEAD;
    actionCounter = entityParams["JUMPER_DEATH_DURATION"];
}

bool Jumper::isDead() {
    return (actionState == JUMPER_DEAD || actionState == JUMPER_DYING);
}

bool Jumper::isRemovable() {
    return (actionCounter == 0 && actionState == JUMPER_DEAD);
}

Jumper::~Jumper() {}