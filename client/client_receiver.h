#ifndef CLIENT_RECEIVE_H
#define CLIENT_RECEIVE_H

#include "client_protocol.h"
#include "action_client.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"
#include "queue.h"
#include "client_game_state.h"

class ReceiverThread : public Thread {
   public:
    ReceiverThread(bool& wasClosed,
                    ClientProtocol& protocol, 
                    Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender);

    virtual void run() override;

   private:
    bool& wasClosed;
    ClientProtocol& protocol;
    Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender;

    void inGame();
};

#endif  // CLIENT_RECEIVE_H