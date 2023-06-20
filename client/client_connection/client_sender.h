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
    SenderThread(std::atomic<bool>& isConnected,
                ClientProtocol& protocol, 
                Queue<std::shared_ptr<ActionClient>>& qEventsToSender);

    virtual void run() override;

   private:
    std::atomic<bool>& isConnected;
    ClientProtocol& protocol;
    Queue<std::shared_ptr<ActionClient>>& qEventsToSender;

    void inGame();
};

#endif  // CLIENT_SENDER_H