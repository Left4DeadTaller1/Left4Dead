#include "jumper.h"

#include <cmath>

#include "game_config.h"

Jumper::Jumper(int xPosition, int yPosition, std::string zombieId, int mutationLevel)
    : Zombie(xPosition, yPosition, zombieId, mutationLevel), actionState(JUMPER_IDLE), hasCrashed(false) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * (spawnParams["MUTATION_STRENGTH"] / 10);

    width = entityParams["JUMPER_WIDTH"];
    height = entityParams["JUMPER_HEIGHT"];
    health = entityParams["JUMPER_HEALTH"] * (1 + mutationIncrease);
    movementSpeed = entityParams["JUMPER_SPEED"] * (1 + mutationIncrease);
    // Todo: add jump ATk
    attacksCooldowns.insert(std::make_pair("melee", 0));
    attacksCooldowns.insert(std::make_pair("jump", 0));
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

Attack Jumper::generateAttack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * (spawnParams["MUTATION_STRENGTH"] / 10);
    int atkDmg = entityParams["JUMPER_ATTACK_DAMAGE"] * (1 + mutationIncrease);
    int attackRange = entityParams["JUMPER_ATTACK_RANGE"];
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

Attack Jumper::generateJumpAttack() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    std::map<std::string, int> spawnParams = config.getSpawnsParams();
    int mutationIncrease = mutationLevel * (spawnParams["MUTATION_STRENGTH"] / 10);
    int atkDmg = entityParams["JUMPER_JUMP_DAMAGE"] * (1 + mutationIncrease);
    int attackRange = entityParams["JUMPER_JUMP_RANGE"];
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
    return Attack(JUMP, atkDmg, attackX, attackDirection, y, y + height, attackRange);
}

void Jumper::attackPlayer() {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    attacksCooldowns["melee"] = entityParams["JUMPER_ATTACK_COOLDOWN"];
    actionState = JUMPER_ATTACKING;
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

bool Jumper::takeDamage(int damage) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    health -= damage;
    if (health <= 0) {
        health = 0;
        actionState = JUMPER_DYING;
        actionCounter = entityParams["JUMPER_DYING_DURATION"];
        return true;
    } else {
        actionState = JUMPER_HURT;
        actionCounter = entityParams["JUMPER_HURT_DURATION"];
        return false;
    }
    return false;
}

void Jumper::useSkill(std::vector<std::shared_ptr<Entity>>& players) {
    // TODO just change it to a nullptr
    if (attacksCooldowns["jump"] != 0)
        return;

    if (getplayerWithinRange(players)) {
        GameConfig& config = GameConfig::getInstance();
        std::map<std::string, int> entityParams = config.getEntitiesParams();

        attacksCooldowns["jump"] = entityParams["JUMPER_JUMP_COOLDOWN"];
        actionState = JUMPER_JUMPING;
        actionCounter = entityParams["JUMPER_JUMP_DURATION"];
        hasCrashed = false;
    }
}

std::shared_ptr<Ability> Jumper::getActiveSkill() {
    std::shared_ptr<Ability> jumpAbility = std::make_shared<Ability>();
    jumpAbility->type = JUMP_ABILITY;
    return jumpAbility;
}

bool Jumper::getplayerWithinRange(std::vector<std::shared_ptr<Entity>>& entities) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> entityParams = config.getEntitiesParams();
    int maxJumpRange = entityParams["JUMPER_JUMP_DISTANCE"];

    for (const auto& entity : entities) {
        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(entity);
        if (player) {
            if (player->isDead())
                continue;
            int distance = std::sqrt(std::pow((x - player->getX()), 2) + std::pow((y - player->getY()), 2));
            if (distance <= maxJumpRange) {
                return true;
            }
        }
    }
    return false;
}

bool Jumper::getHasCrashed() {
    return hasCrashed;
}

void Jumper::startCrashing() {
    hasCrashed = true;
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

JumperActionState Jumper::getActionState() {
    return actionState;
}

Jumper::~Jumper() {}