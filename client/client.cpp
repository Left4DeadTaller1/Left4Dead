#include "client.h"

Client::Client(const char* hostname, const char* servname, 
                SDL2pp::Window& window, ClientProtocol& protocol) : 
                                            wasClosed(false),
                                            protocol(protocol),
                                            isConnected(true),
                                            qEventsToSender(TAM_MAX_QUEUE),
                                            qServerToRender(TAM_MAX_QUEUE),
                                            qEventsToRender(TAM_MAX_QUEUE),
                                            window(window),
                                            renderer(isConnected, qServerToRender, qEventsToRender, 
                                            window, protocol),
                                            senderThread(isConnected, protocol, qEventsToSender),
                                            receiverThread(isConnected, protocol, qServerToRender),
                                            eventManagerThread(qEventsToSender,
                                                            qEventsToRender,
                                                            window,
                                                            isConnected) {}


void Client::run() { try {
        eventManagerThread.start();
        senderThread.start();
        receiverThread.start();
        renderer.looprender();
    } catch (const std::exception &e) {
        std::cerr << "Client: Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client: Unknown exception caught. Ending program." << std::endl;
    }
}

Client::~Client() {
    eventManagerThread.join();
    senderThread.join();
    receiverThread.join();
}
