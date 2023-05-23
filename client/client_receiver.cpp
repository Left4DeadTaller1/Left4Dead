#include "client_receiver.h"

ReceiverThread::ReceiverThread(bool& wasClosed, ClientProtocol& protocol, 
                                Queue<Action*>& qServerToRender): 
                                wasClosed(wasClosed),
                                protocol(protocol),
                                qServerToRender(qServerToRender){}

void ReceiverThread::inGame(){
    while (!wasClosed) {
        //aca recibe el objeto DTO y le tiene que mandar al render
        //action.recv(protocol, wasClosed);

        //qServerToRender.push()
    }
}

void ReceiverThread::run() {
    try {
        inGame();
    } catch (const LibError& e) {
        //wasClosed = true;
    }
}