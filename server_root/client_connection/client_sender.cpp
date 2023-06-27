#include "client_sender.h"

ClientSender::ClientSender(Socket &skt, Queue<std::shared_ptr<std::vector<uint8_t>>> &gameResponses)
    : clientSocket(skt),
      gameResponses(gameResponses),
      isRunning(false),
      protocol() {}

void ClientSender::run() {
    isRunning = true;
    try {
        while (isRunning) {
            // Now gameSnapShot is a vector of bytes representing the game state
            std::shared_ptr<std::vector<uint8_t>> gameSnapShotPtr = gameResponses.pop();

            if (gameSnapShotPtr == nullptr) {
                // TODO: maybe add an error throw or smthing
                std::cout << "EN PUNTERO ES NULL\n";
                continue;
            }

            std::vector<uint8_t> gameSnapShot = *gameSnapShotPtr;

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
        // The queue is closed.
        stop();
        std::cerr << "ClientSender: Queue is closed. Ending thread." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "ClientSender: Exception caught: " << e.what() << std::endl;
    } catch (...) {
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
