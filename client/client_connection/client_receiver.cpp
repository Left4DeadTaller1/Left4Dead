#include "client_receiver.h"

ReceiverThread::ReceiverThread(std::atomic<bool>& isConnected,
                                ClientProtocol& protocol, 
                                Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender): 
                                isConnected(isConnected),
                                protocol(protocol),
                                qServerToRender(qServerToRender){}


void ReceiverThread::run() {
    //implem asi va a esperar la resp del servidor, 
    //si quiero que no la espere, hay que poner: 
    //wasClosed = true de client_sender y avisarle al render 
    //pusheando en event manager a la cola del render directo
    bool wasClosed = false;
    while (!wasClosed && isConnected) {
        try {
            int messageType = protocol.receiveTypeCommand(wasClosed);
            if (messageType == MSG_CREATE){
                continue;
            }
            if (messageType == MSG_JOIN){
                continue;
            }
            if (messageType == MSG_EXIT){
                continue;
            }
            if (messageType == MSG_GAME_STATE){
                std::shared_ptr<gameStateDTO_t> gameStateDTO = protocol.receiveStateGame(wasClosed);
                qServerToRender.push(gameStateDTO);
            }
        } catch (const ClosedQueue&) {
            break;
        }
    }
    isConnected = false;
}