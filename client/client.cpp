#include "client.h"

Client::Client(const char* hostname, const char* servname, 
                SDL2pp::Window& window, MainWindow& windowQT) : wasClosed(false),
                                                                protocol(hostname, servname),
                                                                isConnected(true),
                                                                qEventsToSender(TAM_MAX_QUEUE),
                                                                qServerToRender(TAM_MAX_QUEUE),
                                                                qEventsToRender(TAM_MAX_QUEUE),
                                                                window(window),
                                                                windowQT(windowQT),
                                                                renderer(isConnected, qServerToRender, qEventsToRender, window),
                                                                senderThread(isConnected, protocol, qEventsToSender),
                                                                receiverThread(isConnected, protocol, qServerToRender),
                                                                eventManagerThread(qEventsToSender,
                                                                                qEventsToRender,
                                                                                window,
                                                                                isConnected) {}

void Client::sendInitialAction() {
    std::string type = windowQT.getInicialActionType();
    if (type == "create"){
        std::string namePlayer = windowQT.getNamePlayer();
        std::shared_ptr<ActionClient> action = std::make_shared<Create>(namePlayer);
        qEventsToSender.push(action);
    }
    if (type == "join"){
        std::string namePlayer = windowQT.getNamePlayer();
        std::string code = windowQT.getCodeGame();
        std::shared_ptr<ActionClient> action = std::make_shared<Join>(std::stoi(code), namePlayer);
        qEventsToSender.push(action);
    }
}


void Client::run() { try {
    sendInitialAction();
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
