#include "action.h"

Action::Action()
    : playerId(""), movementType(ACTION_IDLE), directionXType(ACTION_NONE_X), directionYType(ACTION_NONE_Y), weaponState(ACTION_WEAPON_IDLE) {}

Action::Action(std::string playerId, int movementType, int directionXType, int directionYType, int weaponState)
    : playerId(playerId) {
    this->movementType = static_cast<MovementType>(movementType);
    this->directionXType = static_cast<DirectionXType>(directionXType);
    this->directionYType = static_cast<DirectionYType>(directionYType);
    this->weaponState = static_cast<ActionWeaponState>(weaponState);
}

std::string Action::getId() {
    return playerId;
}

// TODO: this could prob just return the Enum type instead of int, so you don't habvet to cast in game when optaining state
int Action::getMovementType() {
    return static_cast<int>(movementType);
}

int Action::getDirectionXType() {
    return static_cast<int>(directionXType);
}

int Action::getDirectionYType() {
    return static_cast<int>(directionYType);
}

int Action::getWeaponState() {
    return static_cast<int>(weaponState);
}

Action::~Action() {}
