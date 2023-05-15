#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <memory>

#include "dipa_classes/socket.h"
#include "dipa_classes/thread.h"
#include "server_root/client_connection/client_connection.h"

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
