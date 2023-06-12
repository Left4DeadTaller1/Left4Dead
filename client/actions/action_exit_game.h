#ifndef ACTION_EXIT_GAME_H_
#define ACTION_EXIT_GAME_H_

#include "action_client.h"
#include <memory>

class Exit : public ActionClient {
   public:
    std::vector<int8_t> serialize() const;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_EXIT_MOVE_H_