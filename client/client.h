#ifndef CLIENT_H
#define CLIENT_H

#include <SDL2pp/SDL2pp.hh>
#include <exception>
#include <string>
#include <vector>

#include "client_event_manager.h"
#include "client_protocol.h"
#include "client_sender.h"
#include "client_render.h"
#include "client_action/action.h"
#include "liberror.h"
#include "queue.h"
#include "socket.h"
#include "thread.h"

#define TAM_MAX_QUEUE 16000

using namespace SDL2pp;

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
    Queue<Action*> qEventsToSender;
    Queue<Action*> qServerToRender;
    Queue<Action*> qEventsToRender;
    Window& window;
    ClientRenderer renderer;
    SenderThread senderThread;
    EventManagerThread eventManagerThread;

    void leave();
};

#endif  // CLIENT_H
