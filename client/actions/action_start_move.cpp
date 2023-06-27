#include "action_start_move.h"

StartMove::StartMove(TypeMove typeMove, DirectionMove directionMove): typeMove(typeMove),
                                                                        dirX(0),
                                                                        dirY(0){
    if (directionMove == RIGHT){
        dirX = 1;
        dirY = 3;
    }
    if (directionMove == LEFT){
        dirX = 0;
        dirY = 3;
    }
    if (directionMove == UP){
        dirX = 3;
        dirY = 0;
    }
    if (directionMove == DOWN){
        dirX = 3;
        dirY = 1;
    }
}

std::vector<int8_t> StartMove::serialize() const {
    std::vector<int8_t> data = {START_MOVE, static_cast<int8_t>(typeMove), dirX, dirY};
    return data;
};
