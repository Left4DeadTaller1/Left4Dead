#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "dipa_classes/thread.h"

class ReceivingThread : public Thread {
   public:
    // Receiver para el menu, pre-partida...

    // Receiver para cuando ya se esta en al partida
    ReceivingThread(Socket& socket)
        : socket(socket),
          // serverMessagesQueue(serverMessagesQueue), queue de acciones
          // protocol(protocol),
          running(false);

    virtual void run() override;

    bool isRunning();

   private:
    Socket& socket;
    // Queue<std::string>& serverMessagesQueue;
    // Protocol& protocol;
    bool running;
};

#endif  // CLIENT_RECEIVER_H