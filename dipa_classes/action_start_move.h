#ifndef ACTION_START_MOVE_H_
#define ACTION_START_MOVE_H_

#include "action_client.h"
#include <memory>

typedef struct StartMoveDTO {
    int idPlayer;
    int dirX;
    int dirY;
} StartMoveDTO_t;

class StartMove : public ActionClient {
   private:
    int idPlayer;
    int dirX;
    int dirY;

   public:
    StartMove(int idPlayer, int difx, int dify);

    virtual actionDTO_t* getDTO() const override;

    //virtual void run(Game& game) override;
};

#endif  // ACTION_START_MOVE_H_