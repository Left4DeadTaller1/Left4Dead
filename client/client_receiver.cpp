#include "client_receiver.h"

ReceivingThread::ReceivingThread(Socket& socket)
    : socket(socket),
      // serverMessagesQueue(serverMessagesQueue), queue de acciones
      // protocol(protocol),
      running(false) {}

void ReceivingThread::run() {
    running = true;
    bool was_closed = false;
    try {
        while (!was_closed) {
            // std::string serverMessage = protocol.receiveBroadcastMessage(socket, was_closed);

            // if (!serverMessage.empty()) {
            //     serverMessagesQueue.push(serverMessage);
            // }
        }
    }

    catch (const LibError& e) {
        // supongo que esto no hace falta realmente porque si hubo un liberror
        // el while se interrumpio pero bueno no esta de mas
        was_closed = true;
    }
}

bool ReceivingThread::isRunning() { return running; }