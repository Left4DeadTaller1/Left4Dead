#include "client.h"

Client::Client(const char* hostname, const char* servname, SDL2pp::Window& window) : socket(hostname, servname),
                                                                             wasClosed(false),
                                                                             protocol(socket),
                                                                             isConnected(true),
                                                                             qEventsToSender(TAM_MAX_QUEUE),
                                                                             qServerToRender(TAM_MAX_QUEUE),
                                                                             qEventsToRender(TAM_MAX_QUEUE),
                                                                             window(window),
                                                                             renderer(qServerToRender, qEventsToRender, window),
                                                                             senderThread(wasClosed, protocol, qEventsToSender),
                                                                             receiverThread(wasClosed, protocol, qServerToRender),
                                                                             eventManagerThread(qEventsToSender,
                                                                                                qEventsToRender,
                                                                                                window,
                                                                                                isConnected) {}

void Client::run() { try {
    eventManagerThread.start();
    senderThread.start();
    receiverThread.start();
    std::cout << "antes de llamar a render\n";
    renderer.render();
    } catch(...){
        //implem
    }
}

Client::~Client() {
    eventManagerThread.join();
    senderThread.join();
    receiverThread.join();
}
