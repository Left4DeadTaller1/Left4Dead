#include "client_receiver.h"

ReceiverThread::ReceiverThread(bool& wasClosed, ClientProtocol& protocol, 
                                Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender): 
                                wasClosed(wasClosed),
                                protocol(protocol),
                                qServerToRender(qServerToRender){}

void ReceiverThread::run() { try {
        //implem asi va a esperar la resp del servidor, 
        //si quiero que no la espere, hay que poner: 
        //wasClosed = true de client_sender y avisarle al render 
        //pusheando en event manager a la cola del render directo
        while (!wasClosed) {
            std::shared_ptr<gameStateDTO_t> gameStateDTO = protocol.receiveStateGame(wasClosed);
            qServerToRender.push(gameStateDTO);
        }
        wasClosed = true;
    } catch (const LibError& e) {
        //implem;
    }
}