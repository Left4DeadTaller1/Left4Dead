#ifndef MOVE_H_
#define MOVE_H_

#include "action.h"
#include "game.h"

class Move : public Action {
   private:
    int idPlayer;
    int deltaX;
    int deltaY;

   public:
    Move(int idPlayer, int difx, int dify);

    virtual void run(Game& Game) override;
};

#endif  // MOVE_H_