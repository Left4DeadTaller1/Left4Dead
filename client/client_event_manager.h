#ifndef CLIENT_EVENT_MANAGER_H
#define CLIENT_EVENT_MANAGER_H

#include "queue.h"
#include "thread.h"

class EventManager : public Thread {
    private:
    Queue<std::string>& queue_sender;
    Queue<std::string>& queue_render;

    public:
    EventManager(Queue<std::string>& queue_sender, Queue<std::string>& queue_render);

    virtual void run() override;
};

#endif  // CLIENT_EVENT_MANAGER_H