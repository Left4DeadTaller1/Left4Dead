#include "action_start_move.h"

StartMove::StartMove(TypeMove typeMove, DirectionMove directionMove): typeMove(typeMove),
                                                                        dirX(0),
                                                                        dirY(0){
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

std::vector<int8_t> StartMove::serialize() const {
    //harcodeo 0 pero deberia ser typeMove
    std::vector<int8_t> data = {START_MOVE, 0, dirX, dirY};
    return data;
};