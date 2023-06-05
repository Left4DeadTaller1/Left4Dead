#include "action.h"

Action::Action(int playerId, int actionType)
    : playerId(playerId) {
    // this is just for safety realistically you are not going to get an invalid action type
    if (actionType < 0 || actionType > 2) {
        this->actionType = ActionType::INVALID;
    } else {
        this->actionType = static_cast<ActionType>(actionType);
    }
}

Action::~Action() {}
