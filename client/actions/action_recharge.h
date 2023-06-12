#ifndef ACTION_RECHARGE_H_
#define ACTION_RECHARGE_H_

#include "action_client.h"
#include <memory>

class Recharge : public ActionClient {
   public:
    std::vector<int8_t> serialize() const;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_RECHARGE_H_