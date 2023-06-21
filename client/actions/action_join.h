#ifndef ACTION_JOIN_H_
#define ACTION_JOIN_H_

#include "action_client.h"
#include <memory>
#include <string>

class Join : public ActionClient {
   private:
    int8_t code;
    std::string namePlayer;

   public:
    Join(int8_t code, std::string namePlayer);

    virtual std::vector<int8_t> serialize() const override;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_JOIN_H_

