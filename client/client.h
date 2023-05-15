#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "common_liberror.h"
#include "common_protocol.h"
#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"

// /* ************************************************************************* *
//  *Client User Api to type msgs in the terminal
//  * ************************************************************************* */

class Client {
   public:
    Client(const char* hostname, const char* servname);
    ~Client();

    void run();

   private:
    Socket socket;
    // Protocol protocol;
    // Queue<std::string> serverMessagesQueue;
    ReceivingThread receivingThread;
    bool isConnected;

    void processCommands();

    void leave();
};

#endif  // CLIENT_H