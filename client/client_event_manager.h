#ifndef CLIENT_EVENT_MANAGER_H
#define CLIENT_EVENT_MANAGER_H

#include "queue.h"
#include "thread.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class EventManagerThread : public Thread {
    private:
    Queue<std::string>& queueSenderGame;
    Queue<std::string>& queueRenderEvent;
    Window& window;
    bool& isConnected;

    public:
    EventManagerThread(Queue<std::string>& queueSenderGame, 
                Queue<std::string>& queueRenderEvent, 
                Window& window, bool& isConnected);

    virtual void run() override;
};

#endif  // CLIENT_EVENT_MANAGER_H
