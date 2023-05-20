#include "client_receiver.h"

#include "liberror.h"

ReceivingThread::ReceivingThread(Socket& socket, ClientProtocol& protocol, 
                                Queue<std::string>& queueRenderGame): 
                                socket(socket),
                                protocol(protocol),
                                queueRenderGame(queueRenderGame),
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