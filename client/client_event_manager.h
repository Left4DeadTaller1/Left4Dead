#ifndef CLIENT_EVENT_MANAGER_H
#define CLIENT_EVENT_MANAGER_H

#include "queue.h"
#include "thread.h"
#include <SDL2pp/SDL2pp.hh>
#include "action_client.h"

//actions
#include "action_create.h"
#include "action_start_move.h"
#include "action_end_move.h"
#include "action_join.h"
#include "action_start_game.h"
#include "action_exit_game.h"
#include "action_recharge.h"
#include "action_start_shoot.h"
#include "action_end_shoot.h"

class EventManagerThread : public Thread {
    private:
    Queue<std::shared_ptr<ActionClient>>& qEventsToSender;
    Queue<std::shared_ptr<ActionClient>>& qEventsToRender;
    SDL2pp::Window& window;
    bool& isConnected;

    public:
    EventManagerThread(Queue<std::shared_ptr<ActionClient>>& qEventsToSender,
                        Queue<std::shared_ptr<ActionClient>>& qEventsToRender,
                        SDL2pp::Window& window, bool& isConnected);

    virtual void run() override;
};

#endif  // CLIENT_EVENT_MANAGER_H
