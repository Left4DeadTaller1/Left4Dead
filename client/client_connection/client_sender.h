#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include "client_protocol.h"
#include "action_client.h"
#include "client_receiver.h"
#include "socket.h"
#include "thread.h"
#include "queue.h"
#include "liberror.h"
#include <atomic>

class SenderThread : public Thread {
    private:
    std::atomic<bool>& isConnected;
    ClientProtocol& protocol;
    Queue<std::shared_ptr<ActionClient>>& qEventsToSender;

    void inGame();

    public:
    SenderThread(std::atomic<bool>& isConnected,
                ClientProtocol& protocol, 
                Queue<std::shared_ptr<ActionClient>>& qEventsToSender);

    virtual void run() override;

    ~SenderThread();
};

#endif  // CLIENT_SENDER_H