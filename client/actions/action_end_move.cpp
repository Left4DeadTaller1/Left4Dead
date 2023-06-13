#include "action_end_move.h"

EndMove::EndMove(DirectionMove directionMove){
    if (directionMove == RIGHT){
        dirX = 1;
        dirY = 2;
    }
    if (directionMove == LEFT){
        dirX = 0;
        dirY = 2;
    }
    if (directionMove == UP){
        dirX = 2;
        dirY = 0;
    }
    if (directionMove == DOWN){
        dirX = 2;
        dirY = 1;
    }
}

std::vector<int8_t> EndMove::serialize() const {
    std::vector<int8_t> data = {END_MOVE, dirX, dirY};
    return data;
};

bool EndMove::isExit(void) const {
    return false;
}
