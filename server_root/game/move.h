#ifndef MOVE_H_
#define MOVE_H_

#include "action.h"
#include "game_state.h"

class Move : public Action{
    private:
    int idPlayer;
    int difx;
    int dify;

    public:
    Move(int idPlayer, int difx, int dify);

    virtual void run(GameState& gameState) override;
};

#endif //MOVE_H_