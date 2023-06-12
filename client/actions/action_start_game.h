#ifndef ACTION_START_GAME_H_
#define ACTION_START_GAME_H_

#include "action_client.h"
#include <memory>

class StartGame : public ActionClient {
   public:
    std::vector<int8_t> serialize() const;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_START_GAME_H_
