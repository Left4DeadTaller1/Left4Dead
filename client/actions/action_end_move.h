#ifndef ACTION_END_MOVE_H_
#define ACTION_END_MOVE_H_

#include "action_client.h"
#include <memory>
#include <iostream>

class EndMove : public ActionClient {
   private:
    int8_t dirX;
    int8_t dirY;

   public:
    EndMove(DirectionMove directionMove);

    virtual std::vector<int8_t> serialize() const override;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_END_MOVE_H_

