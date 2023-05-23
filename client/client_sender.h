#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include "client_protocol.h"
#include "client_action/action.h"
#include "client_receiver.h"
#include "socket.h"
#include "thread.h"
#include "queue.h"
#include "liberror.h"

class SenderThread : public Thread {
   public:
    SenderThread(bool& wasClosed,
                    ClientProtocol& protocol, 
                    Queue<Action*>& qServerToRender,
                    Queue<Action*>& qEventsToSender);

    virtual void run() override;

    ~SenderThread();

   private:
    bool& wasClosed;
    ClientProtocol& protocol;
    Queue<Action*>& qServerToRender;
    Queue<Action*>& qEventsToSender;
    ReceiverThread receiverThread;

    void menu();

    void inGame();
};

#endif  // CLIENT_SENDER_H