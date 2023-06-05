#ifndef ACTION_END_MOVE_H_
#define ACTION_END_MOVE_H_

#include "action_client.h"
#include <memory>

typedef struct EndMoveDTO {
    int idPlayer;
} EndMoveDTO_t;

class EndMove : public ActionClient {
   private:
    int idPlayer;

   public:
    EndMove(int idPlayer);

    actionDTO_t* getDTO() const override;

    //virtual void run(Game& game) override;
};

#endif  // ACTION_END_MOVE_H_