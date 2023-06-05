#ifndef ACTION_H_
#define ACTION_H_

#include <string>

enum MovementType {
    ACTION_WALKING,
    ACTION_RUNNING,
    ACTION_IDLE,
};

enum DirectionXType {
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_NONE_X,
};

enum DirectionYType {
    ACTION_UP,
    ACTION_DOWN,
    ACTION_NONE_Y,
};

class Action {
   private:
    std::string playerId;
    MovementType movementType;
    DirectionXType directionXType;
    DirectionYType directionYType;

   public:
    Action();
    Action(std::string playerId, int movementType, int directionXType, int directionYType);
    ~Action();

    std::string getPlayerId();

    // For testing purposes only do not use in production
    int getMovementType();
    int getDirectionXType();
    int getDirectionYType();
};

#endif  // ACTION_H_
