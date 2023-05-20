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
#include "client_event_manager.h"

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
    //Socket socket;
    // Protocol protocol;
    // Queue<std::string> serverMessagesQueue;
    //ReceivingThread receivingThread;
    bool isConnected;
    Queue<std::string> queue_sender;
    Queue<std::string> queue_render;
    Window& window;
    EventManager eventManager;

    void processUserInput();

    void leave();

    void DrawBackground(Renderer& renderer, Texture& background);

    void DrawSoldier(Renderer& renderer, Texture& soldier, int textureWidth, int textureHeight);
    
    int render(Window& window);
};

#endif  // CLIENT_H