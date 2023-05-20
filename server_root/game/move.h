#ifndef MOVE_H_
#define MOVE_H_

#include "action.h"
#include "game_state.h"

class Move : public Action{
    private:
    int idPlayer;
    int deltaX;
    int deltaY;

    public:
    Move(int idPlayer, int deltaX, int deltaY);

    virtual void run(GameState& gameState) override;
};

#endif //MOVE_H_