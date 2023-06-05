#ifndef CLIENT_EVENT_MANAGER_H
#define CLIENT_EVENT_MANAGER_H

#include "queue.h"
#include "thread.h"
#include <SDL2pp/SDL2pp.hh>
#include "action_client.h"
#include "action_create.h"
#include "action_start_move.h"
#include "action_end_move.h"
#include "action_join.h"
#include "action_start_game.h"
using namespace SDL2pp;

class EventManagerThread : public Thread {
    private:
    Queue<ActionClient*>& qEventsToSender;
    Queue<ActionClient*>& qEventsToRender;
    Window& window;
    bool& isConnected;

    public:
    EventManagerThread(Queue<ActionClient*>& qEventsToSender, 
                Queue<ActionClient*>& qEventsToRender, 
                Window& window, bool& isConnected);

    virtual void run() override;
};

#endif  // CLIENT_EVENT_MANAGER_H
