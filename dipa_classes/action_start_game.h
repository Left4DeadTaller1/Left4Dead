#ifndef ACTION_START_GAME_H_
#define ACTION_START_GAME_H_

#include "action_client.h"
#include <memory>

class StartGame : public ActionClient {
   public:
    virtual actionDTO_t* getDTO() const override;

    //virtual void run(Game& game) override;
};

#endif  // ACTION_START_GAME_H_