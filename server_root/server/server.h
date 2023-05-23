#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <utility>
#include <vector>

#include "socket.h"
// #include "protected_game_codes.h"

class Server {
   private:
    Socket svr_socket;
    Acceptor acep_th;
    // ProtectedGameCodes gameCodes;

   public:
    explicit Server(const char *servname);

    // Method to run the server's main loop
    void run();

    Server::~Server();
};

#endif  // SERVER_H
