#include "client_sender.h"

ClientSender::ClientSender(Socket &skt, Queue<std::vector<uint8_t>> &q)
    : clientSocket(skt),
      queue(q),
      isRunning(false) {}

void ClientSender::menu() {}

void ClientSender::run() {
    isRunning = true;
    try {
        while (isRunning) {
            std::vector<uint8_t> message = queue.pop();
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
