#ifndef CLIENT_EVENT_MANAGER_H
#define CLIENT_EVENT_MANAGER_H

#include "queue.h"
#include "thread.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class EventManager : public Thread {
    private:
    Queue<std::string>& queue_sender;
    Queue<std::string>& queue_render;
    Window& window;

    public:
    EventManager(Queue<std::string>& queue_sender, 
                Queue<std::string>& queue_render, 
                Window& window);

    virtual void run() override;
};

#endif  // CLIENT_EVENT_MANAGER_H