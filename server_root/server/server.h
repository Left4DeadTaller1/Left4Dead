#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "acceptor.h"
#include "socket.h"

class Server {
   private:
    Socket svr_socket;
    Acceptor acep_th;        // Changed from unique_ptr to an actual object
    bool isAcceptorRunning;  // Declare this member variable

   public:
    explicit Server(const char* servname);

    // Method to run the server's main loop
    void run();
    ~Server();
};

#endif  // SERVER_H
