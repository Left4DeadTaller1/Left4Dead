#include "client_sender.h"

SenderThread::SenderThread(std::atomic<bool>& isConnected,
                                ClientProtocol& protocol, 
                                Queue<std::shared_ptr<ActionClient>>& qEventsToSender): 
                                isConnected(isConnected),
                                protocol(protocol),
                                qEventsToSender(qEventsToSender){}

void SenderThread::run() {
    bool wasClosed = false;
    std::shared_ptr<ActionClient> action;
    while (!wasClosed && isConnected) { 
        try {
            action = qEventsToSender.pop();
            protocol.sendAction(std::move(action), wasClosed);
        } catch (const ClosedQueue&) {
            break;
        }catch (const std::exception &e) {
            if(!isConnected){
                break;
            } else {
                std::cerr << "Client Main: Exception caught: " << e.what() << std::endl;
            }
        }
    }
    std::cout << "ENTRA A SALIR DEL SENDER\n";
}

SenderThread::~SenderThread(){
    isConnected = false;
}
