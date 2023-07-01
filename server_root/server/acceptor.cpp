#include "acceptor.h"

#include <memory>
#include <utility>

#include "liberror.h"
#define MY_SHUT_RDWR 2

Acceptor::Acceptor(Socket& skt)
    : skt(skt), gamesManager() {}

void Acceptor::run() {
    try {
        while (true) {
            Socket clientSocket = skt.accept();
            auto th = std::make_shared<ClientConnection>(std::move(clientSocket), gamesManager);
            // th->connectToClient();
            clients.push_back(th);

            // Limpieza de clients viejos
            //reap_dead();

            // remove finished games
            gamesManager.removeFinishedGames();
        }
    } catch (const LibError& e) {
        kill_all();
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred in Acceptor::run(): " << e.what() << std::endl;
    } catch (...) {
        // unknown exception
        std::cerr << "An unknown exception occurred in Acceptor::run()" << std::endl;
    }
}

void Acceptor::reap_dead() {
    // las funciones lambdas en c++ parecen re herejes viniendo de js
    clients.remove_if([](const std::shared_ptr<ClientConnection>& c) {
        c->checkThreads();
        if (c->isRemovable()) {
            std::cout << "LO ENTRA A MATAR\n";
            c->kill();
            return true;
        }
        return false;
    });
}

void Acceptor::kill_all() {
    // We kill all clients
    for (auto& c : clients) {
        c->kill();
    }
    clients.clear();
    // We stop all games
    gamesManager.killGames();
}

void Acceptor::shutdown() {
    skt.shutdown(MY_SHUT_RDWR);
    skt.close();
}

Acceptor::~Acceptor() {
    for (auto& client : clients) {
        client->kill();
    }
}
