#include "server_requester.h"

Requester::Requester(Socket &peer, std::atomic<bool>& was_closed, 
Server_protocol& protocol, Queue<std::string>* queue, 
std::atomic<bool>& is_dead): 
    peer(peer), 
    is_dead_requester(is_dead), 
    was_closed(was_closed), 
    protocol(protocol), 
    queue(queue){}

void Requester::run(){
    while (not was_closed){
        try {
            std::string msg = queue->pop();
            protocol.send_message(msg, peer, was_closed);         
        } catch (const ClosedQueue&) {
            break;
        }
    }
    is_dead_requester = true;
}