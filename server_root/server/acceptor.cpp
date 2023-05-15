#include <memory>
#include <utility>

#include "common_liberror.h"
#include "server_acceptor.h"

Acceptor::Acceptor(Socket& skt /*, ProtectedGameCodes& gameCodes*/)
    : skt(skt) /*, gameCodes(gameCodes), clients(), matchManager()*/ {}

void Acceptor::run() {
    try {
        while (true) {
            Socket clientSocket = skt.accept();
            auto th = std::make_shared<ClientConnection>(std::move(clientSocket) /*, gameCodes, matchManager*/);
            th->startTalking();
            clients.push_back(th);
            reap_dead();
            // Limpieza de clients viejos
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
        if (c->is_dead()) {
            c->kill();
            return true;
        }
        return false;
    });
}

void Acceptor::kill_all() {
    for (auto& c : clients) {
        c->kill();
    }
    clients.clear();
}

void Acceptor::shutdown() {
    skt.shutdown(SHUT_RDWR);
    skt.close();
}

Acceptor::~Acceptor() {
    for (auto& client : clients) {
        client->kill();
    }
}
