#ifndef CLIENT_RECEIVE_H
#define CLIENT_RECEIVE_H

#include "client_protocol.h"
#include "client_action/action.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"
#include "queue.h"

class ReceiverThread : public Thread {
   public:
    ReceiverThread(bool& wasClosed,
                    ClientProtocol& protocol, 
                    Queue<Action*>& qServerToRender);

    virtual void run() override;

   private:
    bool& wasClosed;
    ClientProtocol& protocol;
    Queue<Action*>& qServerToRender;

    void inGame();
};

#endif  // CLIENT_RECEIVE_H