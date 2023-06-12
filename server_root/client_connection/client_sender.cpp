#include "client_sender.h"

ClientSender::ClientSender(Socket &skt, Queue<std::vector<uint8_t>> &gameResponses)
    : clientSocket(skt),
      gameResponses(gameResponses),
      isRunning(false),
      protocol() {}

void ClientSender::menu() {}

void ClientSender::run() {
    isRunning = true;
    try {
        while (isRunning) {
            // Now gameSnapShot is a vector of bytes representing the game state
            std::vector<uint8_t> gameSnapShot = gameResponses.pop();
            bool was_closed = false;

            if (gameSnapShot.size() > 0) {
                clientSocket.sendall(gameSnapShot.data(), gameSnapShot.size(), &was_closed);
            }

            // Connection was interrupted
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
