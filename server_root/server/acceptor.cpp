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
            std::cout << "\nNew client connected" << std::endl;
            auto th = std::make_shared<ClientConnection>(std::move(clientSocket), gamesManager);
            // th->connectToClient();
            clients.push_back(th);

            // Limpieza de clients viejos
            reap_dead();

            // remove finished games
            std::cout << "Removing finished games" << std::endl;
            gamesManager.removeFinishedGames();
            std::cout << "FINISH Removing finished games" << std::endl;
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
    std::cout << "Cleaning old clients" << std::endl;
    // las funciones lambdas en c++ parecen re herejes viniendo de js
    clients.remove_if([](const std::shared_ptr<ClientConnection>& c) {
        c->checkThreads();
        if (c->isRemovable()) {
            std::cout << "Player is removable" << std::endl;
            c->kill();
            return true;
        }
        return false;
    });
}

void Acceptor::kill_all() {
    // We stop all games
    gamesManager.killGames();

    // We kill all clients
    for (auto& c : clients) {
        std::cout << "Player is removable" << std::endl;
        c->kill();
    }
    clients.clear();
}

void Acceptor::shutdown() {
    skt.shutdown(MY_SHUT_RDWR);
    skt.close();
}

Acceptor::~Acceptor() {
    std::cout << "In Acceptor destructor" << std::endl;
    for (auto& client : clients) {
        client->kill();
    }
    std::cout << "Finish Acceptor destructor" << std::endl;
}
