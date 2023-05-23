#ifndef ACTION_H_
#define ACTION_H_

#include "/home/usaurio/Left4Dead/client/client_protocol.h"

class Action {
   public:
    Action(void) {}

    virtual int send(ClientProtocol& protocol, bool& wasClosed) = 0;

    virtual ~Action() {}
};

#endif