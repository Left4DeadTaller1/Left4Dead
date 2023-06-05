#include "server_receiver.h"        
        
Receiver::Receiver(Socket &peer, 
                    GameManager& gameManager, 
                    bool& was_closed,
                    Server_protocol& protocol,
                    Queue<std::shared_ptr<gameStateDTO_t>>* qClient,
                    std::atomic<bool>& is_dead, 
                    int idPlayer): 
                    peer(peer), 
                    is_dead(is_dead), 
                    gameManager(gameManager), 
                    was_closed(was_closed), 
                    protocol(protocol),
                    qClient(qClient), 
                    game(NULL), 
                    idPlayer(idPlayer),
                    qActions(NULL),
                    gameThread(NULL){}

void Receiver::run() {
    while (not was_closed) {
        int tipo_comando = protocol.receive_type_of_command(was_closed, peer);
        if (was_closed) {
            return;
        }
        if (tipo_comando == CREATE){
            std::string name_scenario = protocol.receive_create(was_closed, peer);
            game = gameManager.create(name_scenario, qClient, idPlayer);
            const int code_game = game->getCode();
            //protocol.notify_create(code_game, peer, was_closed);
            std::cout << "Created match: " << code_game << "\n";
        }
        if (tipo_comando == START_GAME){
            qActions = gameManager.startGame(game->getCode());
            break;
        }
        if (tipo_comando == JOIN){
            idPlayer = 1;
            const int code_game = protocol.receive_join(was_closed, peer); 
            //game = gameManager.join(code_game, qClient, idPlayer);
            qActions = gameManager.join(code_game, qClient, idPlayer);
            if (game == NULL){
                std::cout << "Match does not exist: 1\n";
                //protocol.notify_join(0, peer, was_closed);
            } 
            if (game != NULL) {
                std::cout << "Joined to match: " << code_game << "\n";
                //protocol.notify_join(1, peer, was_closed);
            }
            break;
        }
    }

    while (not was_closed) {
        int tipo_comando_ = protocol.receive_type_of_command(was_closed, peer);  
        if (was_closed) {
            break;
        }         
        if (tipo_comando_ == START_MOVE){
            std::vector<int> dir_pos = protocol.receive_start_move(was_closed, peer);
            StartMove* startMove = new StartMove(idPlayer, dir_pos[0], dir_pos[1]);
            qActions->push(startMove);
        }
        if (tipo_comando_ == END_MOVE){
            EndMove* endMove = new EndMove(idPlayer);
            qActions->push(endMove);
        }
    }
    is_dead = true;
}

Receiver::~Receiver(){
    //gameThread->join();
}
