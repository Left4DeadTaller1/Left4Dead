#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "liberror.h"
// #include "protocol.h"
#include "client_receiver.h"
#include "queue.h"
#include "socket.h"
#include "thread.h"

#include <exception>
#include <SDL2pp/SDL2pp.hh>

#define WIDTH_WINDOW 800
#define HEIGHT_WINDOW 600
using namespace SDL2pp;

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

    void processUserInput();

    void leave();

    int render();
};

#endif  // CLIENT_H