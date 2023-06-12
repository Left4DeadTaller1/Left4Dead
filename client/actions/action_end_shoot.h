#ifndef ACTION_END_SHOOT_H_
#define ACTION_END_SHOOT_H_

#include "action_client.h"
#include <memory>

class EndShoot : public ActionClient {
   public:
    std::vector<int8_t> serialize() const;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_END_SHOOT_H_