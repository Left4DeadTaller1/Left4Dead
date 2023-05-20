#ifndef ACTION_H_
#define ACTION_H_

#include "game_state.h"

class Action {
    public:
        Action(void){}

        virtual void run(GameState& gameState) = 0;

        virtual ~Action() {}
};

#endif