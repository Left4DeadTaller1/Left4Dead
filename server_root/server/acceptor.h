#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <memory>

#include "../client_connection/client_connection.h"
#include "socket.h"
#include "thread.h"

class Acceptor : public Thread {
   public:
    Acceptor(Socket &skt /*, ProtectedGameCodes &gameCodes*/);
    void run() override;
    void shutdown();
    ~Acceptor();

   private:
    Socket &skt;
    // ProtectedGameCodes &gameCodes;
    std::list<std::shared_ptr<ClientConnection>> clients;
    // MatchManager matchManager; //monitor de la partida
    void reap_dead();
    void kill_all();
};

#endif  // ACCEPTOR_H
