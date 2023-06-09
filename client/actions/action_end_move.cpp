#include "action_end_move.h"

EndMove::EndMove(DirectionMove directionMove){
    if (directionMove == RIGHT){
        dirX = 1;
        dirY = 0;
    }
    if (directionMove == LEFT){
        dirX = -1;
        dirY = 0;
    }
    if (directionMove == UP){
        dirX = 0;
        dirY = -1;
    }
    if (directionMove == DOWN){
        dirX = 0;
        dirY = 1;
    }
}

std::vector<int8_t> EndMove::serialize() const {
    std::vector<int8_t> data = {END_MOVE, dirX, dirY};
    return data;
};
