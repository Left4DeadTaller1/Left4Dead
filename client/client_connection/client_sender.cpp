#include "client_sender.h"

SenderThread::SenderThread(bool& wasClosed, ClientProtocol& protocol, 
                                Queue<std::shared_ptr<ActionClient>>& qEventsToSender): 
                                wasClosed(wasClosed),
                                protocol(protocol),
                                qEventsToSender(qEventsToSender){}

void SenderThread::run() {
    try {
        std::shared_ptr<ActionClient> action;
        while (!wasClosed && (!action || (action && !action->isExit()))) {
            action = qEventsToSender.pop();
            protocol.sendAction(std::move(action), wasClosed);
        }
    } catch (const LibError& e) {
        //implem
    }
}
