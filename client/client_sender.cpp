#include "client_sender.h"

SenderThread::SenderThread(bool& wasClosed, ClientProtocol& protocol, 
                                Queue<ActionClient*>& qEventsToSender): 
                                wasClosed(wasClosed),
                                protocol(protocol),
                                qEventsToSender(qEventsToSender){}

void SenderThread::run() {
    try {
        ActionClient* action;
        while (!wasClosed) {
            action = qEventsToSender.pop();
            actionDTO* dto = action->getDTO();
            protocol.sendAction(dto, wasClosed);
        }
    } catch (const LibError& e) {
        //wasClosed = true;
    }
}
