#ifndef ACTION_START_MOVE_H_
#define ACTION_START_MOVE_H_

#include "action_client.h"
#include <memory>

class StartMove : public ActionClient {
   private:
    int8_t dirX;
    int8_t dirY;
    TypeMove typeMove;

   public:
    StartMove(TypeMove typeMove, DirectionMove directionMove);

    virtual std::vector<int8_t> serialize() const override;
};

#endif  // ACTION_START_MOVE_H_
