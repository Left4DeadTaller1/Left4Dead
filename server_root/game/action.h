#ifndef ACTION_H_
#define ACTION_H_

#include <string>

enum DirectionXType {
    ACTION_LEFT,
    ACTION_RIGHT,
    NONE_X,
};

enum DirectionYType {
    ACTION_UP,
    ACTION_DOWN,
    NONE_Y,
};

enum Input {
    INPUT_WALKING,    // 0
    INPUT_RUNNING,    // 1
    INPUT_IDLE,       // 2
    INPUT_SHOOTING,   // 3
    INPUT_RELOADING,  // 4
    INPUT_ATTACKING,  // 5
};

class Action {
   private:
    // TODO change this later
    std::string playerId;
    Input input;
    DirectionXType directionXType;
    DirectionYType directionYType;

   public:
    Action();
    Action(std::string playerId, int input, int directionXType, int directionYType);
    ~Action();

    std::string getId();

    // For testing purposes only do not use in production
    int getInputType();
    int getDirectionXType();
    int getDirectionYType();
};

#endif  // ACTION_H_
