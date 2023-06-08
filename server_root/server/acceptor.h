#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <memory>

#include "../client_connection/client_connection.h"
#include "../game/games_manager.h"
#include "socket.h"
#include "thread.h"

class Acceptor : public Thread {
   public:
    Acceptor(Socket &skt);
    void run() override;
    void shutdown();
    ~Acceptor();

   private:
    Socket &skt;
    std::list<std::shared_ptr<ClientConnection>> clients;
    GamesManager gamesManager;
    void reap_dead();
    void kill_all();
};

#endif  // ACCEPTOR_H
