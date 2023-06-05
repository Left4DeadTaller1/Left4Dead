#include "acceptor.h"

Acceptor::Acceptor(Socket skt, GameManager& gameManager, Server_protocol& protocol):
skt(std::move(skt)), 
gameManager(gameManager),
protocol(protocol),
stop_(false) {}

void Acceptor::run() {
    int j = 0;
    std::vector<Client_server*> clients;
    while (true){
        try{
            Socket peer = skt.accept();

            Queue<std::shared_ptr<gameStateDTO_t>>* queue = new Queue<std::shared_ptr<gameStateDTO_t>>(TAM_MAX_COLA);
            clients.push_back(new Client_server(std::move(peer), gameManager, protocol, queue));

            clients[j]->run();
            j++;
        
            auto iter = clients.begin();
            while (iter != clients.end()){
                if ((*iter)->is_dead()){
                    (*iter)->stop();
                    delete (*iter);
                    iter = clients.erase(iter);
                } else {
                    ++iter;
                }
            }
        } catch (const std::exception& err){
            if (stop_){
                break;
            } else{
                std::cerr
                << "Something went wrong and an exception was caught: "
                << err.what()
                << "\n";
            }
        }
    }
    for (Client_server* client : clients) {
        client->stop();
        delete client;
    }
}

void Acceptor::stop(){
    stop_ = true;
    skt.shutdown(2);
    skt.close();
}
