#include "server_sender.h"

Sender::Sender(Socket &peer,
                bool &was_closed, 
                Server_protocol& protocol, 
                Queue<std::shared_ptr<gameStateDTO_t>>* qClient, 
                std::atomic<bool>& is_dead): 
                peer(peer), 
                is_dead(is_dead), 
                was_closed(was_closed), 
                protocol(protocol), 
                qClient(qClient){}

void Sender::run(){
    while (not was_closed){
        try {
            std::shared_ptr<gameStateDTO_t> gameStateDTO = qClient->pop();
            protocol.send_update_game(gameStateDTO, was_closed, peer);
        } catch (const ClosedQueue&) {
            break;
        }
    }
    is_dead = true;
}

//game state
//lista de:
//id_entity
//estado
//posx
//posy
//vida
