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
    while (!wasClosed && (!action || (action && !action->isExit()))) {
        action = qEventsToSender.pop();
        protocol.sendAction(std::move(action), wasClosed);
    }
}
