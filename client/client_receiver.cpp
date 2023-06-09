#include "client_receiver.h"

ReceiverThread::ReceiverThread(bool& wasClosed, ClientProtocol& protocol, 
                                Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender): 
                                wasClosed(wasClosed),
                                protocol(protocol),
                                qServerToRender(qServerToRender){}

void ReceiverThread::run() { try {
        while (!wasClosed) {
            std::shared_ptr<gameStateDTO_t> gameStateDTO = protocol.receiveStateGame(wasClosed);
            qServerToRender.push(gameStateDTO);
        }
    } catch (const LibError& e) {
        //implem;
    }
}