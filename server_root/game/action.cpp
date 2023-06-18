#include "action.h"

Action::Action()
    : playerId(""), input(INPUT_IDLE), directionXType(ACTION_RIGHT) {}

Action::Action(std::string playerId, int input, int directionXType, int directionYType)
    : playerId(playerId) {
    this->input = static_cast<Input>(input);
    this->directionXType = static_cast<DirectionXType>(directionXType);
    this->directionYType = static_cast<DirectionYType>(directionYType);
}

std::string Action::getId() {
    return playerId;
}

int Action::getInputType() {
    return static_cast<int>(input);
}

int Action::getDirectionXType() {
    return static_cast<int>(directionXType);
}

int Action::getDirectionYType() {
    return static_cast<int>(directionYType);
}

Action::~Action() {}
