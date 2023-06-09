#ifndef ACTION_RECHARGE_H_
#define ACTION_RECHARGE_H_

#include "action_client.h"
#include <memory>

class Recharge : public ActionClient {
   public:
    std::vector<int8_t> serialize() const;
};

#endif  // ACTION_RECHARGE_H_