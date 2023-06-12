#ifndef ACTION_CREATE_H_
#define ACTION_CREATE_H_

#include "action_client.h"
#include <string>

class Create : public ActionClient {
   private:
    std::string scenario;

   public:
    Create(std::string scenario);

    virtual std::vector<int8_t> serialize() const override;

    virtual bool isExit(void) const override;
};

#endif  //ACTION_CREATE_H_