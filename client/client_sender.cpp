#include "client_sender.h"

SenderThread::SenderThread(bool& wasClosed, ClientProtocol& protocol, 
                                Queue<Action*>& qServerToRender,
                                Queue<Action*>& qEventsToSender): 
                                
                                wasClosed(wasClosed),
                                protocol(protocol),
                                qServerToRender(qServerToRender),
                                qEventsToSender(qEventsToSender),
                                receiverThread(wasClosed, protocol, qServerToRender){}

void SenderThread::menu(){
    while (!wasClosed) {
        Action* action = qEventsToSender.pop();
        if (action->send(protocol, wasClosed) == -1){ //si retorna -1 se recibio la accion start game                                     
            break;                                      //por ahora retorna -1 con el create
        }
        //action->recv(protocol, wasClosed);
        delete action; //despues lo cambio por un puntero inteligente
    }
}

void SenderThread::inGame(){
    while (!wasClosed) {
        //std::cout << "entra a mandar accion\n";
        Action* action = qEventsToSender.pop();
        action->send(protocol, wasClosed);
        delete action;
    }
}

void SenderThread::run() {
    try {
        menu();
        receiverThread.start();
        inGame();
    } catch (const LibError& e) {
        //wasClosed = true;
    }
}

SenderThread::~SenderThread(){
    receiverThread.join();
}
