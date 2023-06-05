#include "client_receiver.h"

ReceiverThread::ReceiverThread(bool& wasClosed, ClientProtocol& protocol, 
                                Queue<int>& qServerToRender): 
                                wasClosed(wasClosed),
                                protocol(protocol),
                                qServerToRender(qServerToRender){}

void ReceiverThread::run() { try {
        //uint32_t code = protocol.receive_notification_create(wasClosed);
        //std::cout << "Se recibio create/join\n";
        while (!wasClosed) {
        //aca recibe el objeto DTO y le tiene que mandar al render
            //std::vector<int> pos_update = protocol.receive_update_move(wasClosed);
            //std::shared_ptr<gameStateDTO_t> gameStateDTO = protocol.receive_update_game(wasClosed);
            //int x = (*(gameStateDTO->entities))[0]->x;
            //int y = (*(gameStateDTO->entities))[0]->y;
            //qServerToRender.push(x);
            //qServerToRender.push(y);
        }
    } catch (const LibError& e) {
        //wasClosed = true;
    }
}