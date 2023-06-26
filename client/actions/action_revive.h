#ifndef ACTION_REVIVE_H_
#define ACTION_REVIVE_H_

#include "action_client.h"
#include <memory>

class Revive : public ActionClient {
   public:
    std::vector<int8_t> serialize() const;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_REVIVE_H_