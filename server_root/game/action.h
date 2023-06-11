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
};

enum DirectionYType {
    ACTION_UP,
    ACTION_DOWN,
};

enum ActionWeaponState {
    ACTION_SHOOTING,
    ACTION_RELOADING,
    ACTION_WEAPON_IDLE
};

class Action {
   private:
    std::string playerId;
    MovementType movementType;
    DirectionXType directionXType;
    DirectionYType directionYType;
    ActionWeaponState weaponState;

   public:
    Action();
    Action(std::string playerId, int movementType, int directionXType, int directionYType, int weaponState);
    ~Action();

    std::string getId();

    // For testing purposes only do not use in production
    int getMovementType();
    int getDirectionXType();
    int getDirectionYType();
    int getWeaponState();
};

#endif  // ACTION_H_
