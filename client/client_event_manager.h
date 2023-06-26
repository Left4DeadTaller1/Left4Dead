#ifndef CLIENT_EVENT_MANAGER_H
#define CLIENT_EVENT_MANAGER_H

#include "queue.h"
#include "thread.h"
#include <SDL2pp/SDL2pp.hh>
#include "action_client.h"

//actions
#include "action_start_move.h"
#include "action_end_move.h"
#include "action_recharge.h"
#include "action_start_shoot.h"
#include "action_end_shoot.h"
#include "action_render.h"
#include "action_revive.h"


class EventManagerThread : public Thread {
    private:
    Queue<std::shared_ptr<ActionClient>>& qEventsToSender;
    Queue<std::shared_ptr<ActionRender>>& qEventsToRender;
    SDL2pp::Window& window;
    std::atomic<bool>& isConnected;

    public:
    EventManagerThread(Queue<std::shared_ptr<ActionClient>>& qEventsToSender,
                        Queue<std::shared_ptr<ActionRender>>& qEventsToRender,
                        SDL2pp::Window& window, std::atomic<bool>& isConnected);

    virtual void run() override;
};

#endif  // CLIENT_EVENT_MANAGER_H
