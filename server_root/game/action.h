#ifndef ACTION_H_
#define ACTION_H_

#include <string>

enum DirectionXType {
    ACTION_LEFT,   // 0
    ACTION_RIGHT,  // 1
    NONE_X,        // 2
    NO_CHANGE_X    // 3
};

enum DirectionYType {
    ACTION_UP,    // 0
    ACTION_DOWN,  // 1
    NONE_Y,       // 2
    NO_CHANGE_Y   // 3
};

enum Input {
    INPUT_WALKING,    // 0
    INPUT_RUNNING,    // 1
    INPUT_IDLE,       // 2
    INPUT_SHOOTING,   // 3
    INPUT_RELOADING,  // 4
    INPUT_ATTACKING,  // 5
    NO_CHANGE,        // 6
    DISCONNECTION,    // 7
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
    Input getInputType();
    int getDirectionXType();
    int getDirectionYType();
};

#endif  // ACTION_H_
