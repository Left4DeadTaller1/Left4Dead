#ifndef ACTION_H_
#define ACTION_H_

#include "game.h"

class Action {
   public:
    Action(void) {}

    virtual void run(Game& Game) = 0;

    virtual ~Action() {}
};

#endif