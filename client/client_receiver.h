#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "client_protocol.h"
#include "socket.h"
#include "thread.h"
#include "queue.h"

class ReceivingThread : public Thread {
   public:
    // Receiver para el menu, pre-partida...

    ReceivingThread(Socket& socket, 
                    ClientProtocol& protocol, 
                    Queue<std::string>& queueRenderGame);

    virtual void run() override;

    bool isRunning();

   private:
    Socket& socket;
    ClientProtocol& protocol;
    Queue<std::string>& queueRenderGame;
    bool running;
};

#endif  // CLIENT_RECEIVER_H