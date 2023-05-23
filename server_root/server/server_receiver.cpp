#include "server_receiver.h"

Receiver::Receiver(Socket &peer, Games& games, 
                    bool& was_closed,
                    Server_protocol& protocol, 
                    Queue<std::string>* queue, 
                    unsigned int code, 
                    std::atomic<bool>& is_dead): 
                    peer(peer), 
                    is_dead_receiver_(is_dead), 
                    games(games), 
                    was_closed(was_closed), 
                    protocol(protocol), 
                    game(NULL), 
                    requester(peer, was_closed, protocol, queue, is_dead){}

void Receiver::run(){
    int tipo_comando = protocol.receive_type_of_command(was_closed, peer);
    if (was_closed) {
        return;
    }
    if (tipo_comando == CREATE){
        std::string name_scenario = protocol.receive_create(was_closed, peer);
        game = games.create(name_scenario, queue);
        int code_game = game.getCode();
        protocol.notify_create(code_game, peer, was_closed);
        std::cout << "Created match: " << code_game << "\n"; //hacer atomico
    }

    if (tipo_comando == JOIN){
        code_game = protocol.receive_join(was_closed, peer); 
        game = games.join(code_game, queue);
        int code_game = game.getCode();
        protocol.notify_join(exito, peer, was_closed);
        if (game == NULL){
            std::cout << "Match does not exist: 1\n"; //hacer atomico
        } else {
            std::cout << "Joined to match: " << code_game << "\n"; //hacer atomico
        }
    }

    requester.start();

    while (not was_closed) {    
        int tipo_comando_ = protocol.receive_type_of_command(was_closed, peer);           
        if (tipo_comando_ == MOVE){
            //std::string msg = protocol.receive_msg(was_closed, peer);
            //game->broadcast(msg);
        }
    }
}

Receiver::~Receiver(){
    is_dead_receiver_ = true;
    requester.join();
}