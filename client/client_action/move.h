#ifndef MOVE_H_
#define MOVE_H_

#include "action.h"

class Move : public Action {
   private:
    int idPlayer;
    int deltaX;
    int deltaY;

   public:
    Move(int idPlayer, int difx, int dify);

    virtual int send(ClientProtocol& protocol, bool& wasClosed) override;
};

#endif  // MOVE_H_