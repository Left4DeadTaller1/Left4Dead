#ifndef CLIENT_RECEIVE_H
#define CLIENT_RECEIVE_H

#include "client_protocol.h"
#include "action_client.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"
#include "queue.h"
#include "client_game_state.h"
#include <atomic>

class ReceiverThread : public Thread {
    private:
    std::atomic<bool>& isConnected;
    ClientProtocol& protocol;
    Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender;

    public:
    ReceiverThread(std::atomic<bool>& isConnected,
                    ClientProtocol& protocol, 
                    Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender);

    virtual void run() override;

    ~ReceiverThread();
};

#endif  // CLIENT_RECEIVE_H