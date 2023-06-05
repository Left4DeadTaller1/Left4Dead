#ifndef CLIENT_H
#define CLIENT_H

#include <exception>
#include <string>
#include <vector>

#include "client_event_manager.h"
#include "client_protocol.h"
#include "client_sender.h"
#include "client_receiver.h"
#include "client_render.h"
#include "action_client.h"
#include "liberror.h"
#include "queue.h"
#include "socket.h"
#include "thread.h"

#define TAM_MAX_QUEUE 16000

class Client {
   public:
    Client(const char* hostname, const char* servname, Window& window);

    ~Client();

    void run();

   private:
    Socket socket;
    bool wasClosed;
    ClientProtocol protocol;
    bool isConnected;
    Queue<ActionClient*> qEventsToSender;
    Queue<int> qServerToRender;
    Queue<ActionClient*> qEventsToRender;
    Window& window;
    ClientRenderer renderer;
    SenderThread senderThread;
    ReceiverThread receiverThread;
    EventManagerThread eventManagerThread;

    void leave();
};

#endif  // CLIENT_H
