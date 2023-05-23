#include "client.h"

Client::Client(const char* hostname, const char* servname, Window& window) : socket(hostname, servname),
                                                                             wasClosed(false),
                                                                             protocol(socket),
                                                                             isConnected(true),
                                                                             qEventsToSender(TAM_MAX_QUEUE),
                                                                             qServerToRender(TAM_MAX_QUEUE),
                                                                             qEventsToRender(TAM_MAX_QUEUE),
                                                                             window(window),
                                                                             renderer(qServerToRender, qEventsToRender, window),
                                                                             senderThread(wasClosed, protocol, qServerToRender, 
                                                                             qEventsToSender),
                                                                             eventManagerThread(qEventsToSender,
                                                                                                qEventsToRender,
                                                                                                window,
                                                                                                isConnected) {}

void Client::run() {
    eventManagerThread.start();
    senderThread.start();
    renderer.render();
}

Client::~Client() {
    eventManagerThread.join();
    senderThread.join();
}
