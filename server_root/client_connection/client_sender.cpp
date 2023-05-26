#include "client_sender.h"

ClientSender::ClientSender(Socket &skt, Queue<int> &gameResponses)
    : clientSocket(skt),
      gameResponses(gameResponses),
      isRunning(false) {}

void ClientSender::menu() {}

void ClientSender::run() {
    isRunning = true;
    try {
        while (isRunning) {
            // again this in the future should be the GameState SnapShot
            int gameSnapShot = gameResponses.pop();
            bool was_closed = false;
            // clientSocket.sendall(message.data(), message.size(), &was_closed);

            // Conection was interrupted
            if (was_closed) {
                break;
            }
        }
    } catch (const ClosedQueue &e) {
        // The queue is closed, end the thread
        std::cerr << "ClientSender: Queue is closed. Ending thread." << std::endl;
    } catch (const std::exception &e) {
        // Other standard exceptions
        std::cerr << "ClientSender: Exception caught: " << e.what() << std::endl;
    } catch (...) {
        // Other unknown exceptions
        std::cerr << "ClientSender: Unknown exception caught. Ending thread." << std::endl;
    }

    isRunning = false;
}

bool ClientSender::getIsRunning() {
    return isRunning;
}

void ClientSender::stop() {
    isRunning = false;
}

ClientSender::~ClientSender() {
    // Destructor implementation
}
