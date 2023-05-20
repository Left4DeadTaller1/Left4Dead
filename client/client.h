#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "liberror.h"
#include "client_event_manager.h"
#include "client_protocol.h"
#include "client_render.h"
#include "client_receiver.h"
#include "queue.h"
#include "socket.h"
#include "thread.h"

#include <exception>
#include <SDL2pp/SDL2pp.hh>

#define TAM_MAX_QUEUE 1000

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
    Queue<std::string> queueSenderGame;
    Queue<std::string> queueRenderGame;
    Queue<std::string> queueRenderEvent;
    Window& window;
    ClientRenderer renderer;
    ReceivingThread receiveThread;
    EventManagerThread eventManagerThread;

    void leave();
};

#endif  // CLIENT_H
