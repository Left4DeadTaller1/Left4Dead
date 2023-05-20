#include "client.h"

Client::Client(const char* hostname, const char* servname, Window& window) : 
                                                            socket(hostname, servname),
                                                            protocol(hostname, servname),
                                                            isConnected(true),
                                                            queueSenderGame(TAM_MAX_QUEUE),
                                                            queueRenderGame(TAM_MAX_QUEUE),
                                                            queueRenderEvent(TAM_MAX_QUEUE),
                                                            window(window),
                                                            renderer(queueRenderGame, queueRenderEvent, window),
                                                            receiveThread(socket, protocol, queueRenderGame),
                                                            eventManagerThread(queueSenderGame, 
                                                                            queueRenderEvent, 
                                                                            window, 
                                                                            isConnected){}


void Client::run() {
    renderer.render();
    eventManagerThread.start();
    receiveThread.start();
}

Client::~Client() {
    eventManagerThread.join();
    receiveThread.join();
}
