#ifndef CLIENT_H
#define CLIENT_H

#include <SDL2pp/SDL2pp.hh>
#include <exception>
#include <string>
#include <vector>

#include "client_event_manager.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "client_render.h"
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
    ClientProtocol protocol;
    bool isConnected;
    Queue<std::string> queueSenderGame;   // qSenderToServer
    Queue<std::string> queueRenderGame;   // qServerToRender
    Queue<std::string> queueRenderEvent;  // qEventsToRender
    Window& window;
    ClientRenderer renderer;
    ReceivingThread receiveThread;
    EventManagerThread eventManagerThread;

    void leave();
};

#endif  // CLIENT_H
