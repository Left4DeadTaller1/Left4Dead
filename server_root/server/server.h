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
    // ProtectedGameCodes gameCodes;

   public:
    explicit Server(const char *servname);

    // Method to run the server's main loop
    void run();
};

#endif  // SERVER_H
