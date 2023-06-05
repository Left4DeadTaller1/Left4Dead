#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include "client_protocol.h"
#include "action_client.h"
#include "client_receiver.h"
#include "socket.h"
#include "thread.h"
#include "queue.h"
#include "liberror.h"

class SenderThread : public Thread {
   public:
    SenderThread(bool& wasClosed,
                    ClientProtocol& protocol, 
                    Queue<ActionClient*>& qEventsToSender);

    virtual void run() override;

   private:
    bool& wasClosed;
    ClientProtocol& protocol;
    Queue<ActionClient*>& qEventsToSender;

    void menu();

    void inGame();
};

#endif  // CLIENT_SENDER_H