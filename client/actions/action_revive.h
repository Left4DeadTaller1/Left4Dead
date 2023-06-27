#ifndef ACTION_REVIVE_H_
#define ACTION_REVIVE_H_

#include "action_client.h"
#include <memory>

class Revive : public ActionClient {
   public:
    std::vector<int8_t> serialize() const;
};

#endif  // ACTION_REVIVE_H_