#ifndef CLIENT_EVENT_MANAGER_H
#define CLIENT_EVENT_MANAGER_H

#include "queue.h"
#include "thread.h"
#include <SDL2pp/SDL2pp.hh>
#include "client_action/action.h"
#include "client_action/move.h"
using namespace SDL2pp;

class EventManagerThread : public Thread {
    private:
    Queue<Action*>& qEventsToSender;
    Queue<Action*>& qEventsToRender;
    Window& window;
    bool& isConnected;

    public:
    EventManagerThread(Queue<Action*>& qEventsToSender, 
                Queue<Action*>& qEventsToRender, 
                Window& window, bool& isConnected);

    virtual void run() override;
};

#endif  // CLIENT_EVENT_MANAGER_H
