#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "acceptor.h"
#include "socket.h"

class Server {
   private:
    Socket svr_socket;
    std::unique_ptr<Acceptor> acep_th;

   public:
    explicit Server(const char *servname);

    // Method to run the server's main loop
    void run();
    ~Server();
};

#endif  // SERVER_H
