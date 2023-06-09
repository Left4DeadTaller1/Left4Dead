#ifndef ACTION_JOIN_H_
#define ACTION_JOIN_H_

#include "action_client.h"
#include <memory>

class Join : public ActionClient {
   private:
    int8_t code;

   public:
    Join(int8_t code);

    virtual std::vector<int8_t> serialize() const override;
};

#endif  // ACTION_JOIN_H_

