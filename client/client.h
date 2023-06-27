#ifndef CLIENT_H
#define CLIENT_H

#include <exception>
#include <string>
#include <vector>

#include "client_event_manager.h"
#include "client_protocol.h"
#include <SDL2pp/SDL2pp.hh>
#include "client_sender.h"
#include "client_receiver.h"
#include "client_render.h"
#include "action_client.h"
#include "liberror.h"
#include "queue.h"
#include "socket.h"
#include "thread.h"
#include <atomic>
#include "action_render.h"

#define TAM_MAX_QUEUE 16000

class Client {
   public:
    Client(const char* hostname, const char* servname, 
            SDL2pp::Window& window, ClientProtocol& protocol,
            MainWindow& windowQT);

    ~Client();

    void run();

   private:
    std::atomic<bool> wasClosed;
    ClientProtocol& protocol;
    std::atomic<bool> isConnected;
    Queue<std::shared_ptr<ActionClient>> qEventsToSender;
    Queue<std::shared_ptr<gameStateDTO_t>> qServerToRender;
    Queue<std::shared_ptr<ActionRender>> qEventsToRender;
    SDL2pp::Window& window;
    ClientRenderer renderer;
    SenderThread senderThread;
    ReceiverThread receiverThread;
    EventManagerThread eventManagerThread;

    //void sendInitialAction();

    void leave();
};

#endif  // CLIENT_H
