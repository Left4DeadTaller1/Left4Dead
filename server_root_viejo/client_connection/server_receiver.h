#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "thread.h"
#include "socket.h"
#include "../game/games_manager.h"
#include "../game/game_thread.h"
#include "../server/server_protocol.h"
#include "action.h"
#include "action_start_move.h"
#include "action_end_move.h"
#include <string>
#include <atomic>

class Receiver : public Thread {
    private:
        Socket& peer;
        std::atomic<bool>& is_dead;
        GameManager& gameManager;
        bool& was_closed;
        Server_protocol& protocol;
        Queue<std::shared_ptr<gameStateDTO_t>>* qClient;
        Game* game;
        int idPlayer;
        Queue<Action*>* qActions;
        GameThread* gameThread;

    public:
        Receiver(Socket &peer, 
                    GameManager& gameManager, 
                    bool& was_closed,
                    Server_protocol& protocol,
                    Queue<std::shared_ptr<gameStateDTO_t>>* qClient, 
                    std::atomic<bool>& is_dead, 
                    int idPlayer);

        virtual void run() override;

        ~Receiver();
};

#endif
