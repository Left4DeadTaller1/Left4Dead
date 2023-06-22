#include "client_receiver.h"

ReceiverThread::ReceiverThread(std::atomic<bool>& isConnected,
                                ClientProtocol& protocol, 
                                Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender): 
                                isConnected(isConnected),
                                protocol(protocol),
                                qServerToRender(qServerToRender){}


void ReceiverThread::run() {
    bool wasClosed = false;
    while (!wasClosed && isConnected) {
        try {
            int messageType = protocol.receiveTypeCommand(wasClosed);
            if (messageType == MSG_GAME_STATE){
                std::shared_ptr<gameStateDTO_t> gameStateDTO = protocol.receiveStateGame(wasClosed);
                qServerToRender.push(gameStateDTO);
            }
        } catch (const ClosedQueue&) {
            break;
        }
    }
}

ReceiverThread::~ReceiverThread(){
    isConnected = false;
}