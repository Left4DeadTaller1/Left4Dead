#ifndef CREATE_H_
#define CREATE_H_

#include "action.h"

class Create : public Action {
   private:
    std::string scenario;

   public:
    Create(std::string scenario);

    virtual int send(ClientProtocol& protocol, bool& wasClosed) override;
};

#endif  // CREATE_H_