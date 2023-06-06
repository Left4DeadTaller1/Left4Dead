#include "action.h"

Action::Action()
    : playerId(""), movementType(ACTION_IDLE), directionXType(ACTION_NONE_X), directionYType(ACTION_NONE_Y) {}

Action::Action(std::string playerId, int movementType, int directionXType, int directionYType)
    : playerId(playerId) {
    this->movementType = static_cast<MovementType>(movementType);
    this->directionXType = static_cast<DirectionXType>(directionXType);
    this->directionYType = static_cast<DirectionYType>(directionYType);
}

std::string Action::getId() {
    return playerId;
}

int Action::getMovementType() {
    return static_cast<int>(movementType);
}

int Action::getDirectionXType() {
    return static_cast<int>(directionXType);
}

int Action::getDirectionYType() {
    return static_cast<int>(directionYType);
}

Action::~Action() {}
