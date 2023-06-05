#include "client_connection.h"

Client_server::Client_server(Socket peer_, GameManager& gameManager, 
Server_protocol& protocol, Queue<std::shared_ptr<gameStateDTO_t>>* qClient_): peer(std::move(peer_)), 
                                                    is_dead_(false),
                                                    gameManager(gameManager), 
                                                    protocol(protocol),
                                                    was_closed(false),
                                                    idPlayer(0), //inicializar en un numero random?
                                                    receiver(peer, gameManager, was_closed, protocol, qClient_, is_dead_, idPlayer),
                                                    sender(peer, was_closed, protocol, qClient_, is_dead_),
                                                    qClient(qClient_){}

void Client_server::run() {
    try {
        receiver.start();
        sender.start();
    } catch(...) {
        //implem;
    }
}

bool Client_server::is_dead() {
    return is_dead_;
}

void Client_server::stop(){
    qClient->close();
    if (!was_closed){
        peer.shutdown(2);
        peer.close();
    }
    delete qClient;
}

Client_server::~Client_server(){
    receiver.join();
    sender.join();
}
