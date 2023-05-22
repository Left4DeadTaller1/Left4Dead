#include "client_receiver.h"

#include <string>

ClientReceiver::ClientReceiver(Socket &skt, Queue<std::vector<uint8_t>> &q,
                               GamesManager &gamesManager)
    : clientSocket(skt),
      queue(q),
      gamesManager(gamesManager),
      isRunning(false),
      game(nullptr) {}

void ClientReceiver::run() {
    isRunning = true;
    try {
        while (isRunning) {
            // uint8_t action;
            bool was_closed = false;
            // clientSocket.recvall(&action, 1, &was_closed);
            std::string decoded_action = "create";  // Place holder you should get the value from protocol
            // std::string decoded_action = protocol.decodeAction(action);

            // Conection was interrupted
            if (was_closed) {
                break;
            }

            if (decoded_action == "create") {  // This could have been a switch or ENUM
                handleCreateAction(clientSocket, was_closed);
            } else if (decoded_action == "join") {
                handleJoinAction(clientSocket, was_closed);
            }
            // } else if (decoded_action == "broadcast") {
            //     handleBroadcastAction(clientSocket, was_closed);
            // } else {
            //     std::cerr << "Unknown action: " << static_cast<int>(action) << std::endl;
            // }
        }
    }

    catch (const ClosedQueue &e) {
        // The queue is closed, end the thread
        std::cerr << "ClientReceiver: Queue is closed. Ending thread." << std::endl;
    } catch (const std::exception &e) {
        // Other standard exceptions
        std::cerr << "ClientReceiver: Exception caught: " << e.what() << std::endl;
    } catch (...) {
        // Other unknown exceptions
        std::cerr << "ClientReceiver: Unknown exception caught. Ending thread." << std::endl;
    }
    isRunning = false;
}

void ClientReceiver::handleCreateAction(Socket &clientSocket, bool &was_closed) {
    game = gamesManager.createLobby();
    // std::cout << "Created match: " << newGameCode << std::endl;

    // std::vector<uint8_t> createResponse = protocol.encodeCreateResponse(newGameCode);
    // queue.push(createResponse);
}

void ClientReceiver::handleJoinAction(Socket &clientSocket, bool &was_closed) {
    int code = 0;  // placeholder you should get the code from the protocol
    // uint32_t code = protocol.receiveJoinGame(clientSocket, was_closed);

    auto optionalGame = gamesManager.joinLobby(code);
    if (optionalGame.has_value()) {
        game = optionalGame.value();
        // std::cout << "Joined to match: " << code << std::endl;
    } else {
        // std::cout << "Match does not exist: " << code << std::endl;
        return;  // Return early as no more work can be done if the lobby doesn't exist
    }
    // std::vector<uint8_t> joinResponse = protocol.encodeJoinResponse(joinSuccess);
    // queue.push(joinResponse);
}

void ClientReceiver::stop() {
    isRunning = false;
}

bool ClientReceiver::getIsRunning() {
    return isRunning;
}
