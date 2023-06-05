#ifndef ACTION_H_
#define ACTION_H_

enum ActionType {
    MOVE,
    SHOOT,
    RELOAD,
    INVALID
};

class Action {
   private:
    int playerId;
    ActionType actionType;

   public:
    Action(int playerId, int actionType);
    ~Action();
};

#endif  // ACTION_H_
