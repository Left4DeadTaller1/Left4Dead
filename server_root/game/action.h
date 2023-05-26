#ifndef ACTION_H_
#define ACTION_H_

#include "game.h"

class Action {
   private:
    // Add playerId so we know in gameThread from who it came
   public:
    Action(void) {}

    virtual void run(Game& Game) = 0;
    // add later a setPlyerId method so the gameThread can set it

    virtual ~Action() {}
};

#endif