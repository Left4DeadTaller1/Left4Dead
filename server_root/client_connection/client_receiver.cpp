#include "client_receiver.h"

#include <string>

ClientReceiver::ClientReceiver(Socket &skt, Queue<std::vector<uint8_t>> &q)
    : clientSocket(skt),
      queue(q),
      isRunning(false) {}

void ClientReceiver::run() {
    isRunning = true;
    try {
        while (isRunning) {
            // uint8_t action;
            bool was_closed = false;
            // clientSocket.recvall(&action, 1, &was_closed);
            // std::string decoded_action = protocol.decodeAction(action);

            // Conection was interrupted
            if (was_closed) {
                break;
            }

            // if (decoded_action == "create") { //This could have been a switch or ENUM
            //     handleCreateAction(clientSocket, was_closed);
            // } else if (decoded_action == "join") {
            //     handleJoinAction(clientSocket, was_closed);
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

// void ClientReceiver::handleCreateAction(Socket &clientSocket, bool &was_closed) {
//     std::string scenario = protocol.receiveCreateGame(clientSocket, was_closed);
//     uint32_t newGameCode = gameCodes.generateGameCode();
//     matchManager.createMatch(newGameCode, scenario);
//     std::cout << "Created match: " << newGameCode << std::endl;
//     // Add the Client to match
//     matchManager.joinMatch(newGameCode, queue);
//     joinedGameCode = newGameCode;
//     std::vector<uint8_t> createResponse = protocol.encodeCreateResponse(newGameCode);
//     queue.push(createResponse);
// }

// void ClientReceiver::handleJoinAction(Socket &clientSocket, bool &was_closed) {
//     // Game code
//     uint32_t code = protocol.receiveJoinGame(clientSocket, was_closed);

//     bool joinSuccess = gameCodes.isValidGameCode(code);
//     if (joinSuccess) {
//         std::cout << "Joined to match: " << code << std::endl;
//         matchManager.joinMatch(code, queue);
//         joinedGameCode = code;
//     } else {
//         std::cout << "Match does not exist: " << code << std::endl;
//     }
//     std::vector<uint8_t> joinResponse = protocol.encodeJoinResponse(joinSuccess);
//     queue.push(joinResponse);
// }

// void ClientReceiver::handleBroadcastAction(Socket &clientSocket, bool &was_closed) {
//     std::string message = protocol.receiveBroadcastAction(clientSocket, was_closed);
//     std::vector<uint8_t> broadcastMessage = protocol.encodeBroadcast(message, true);
//     matchManager.broadcastToMatch(joinedGameCode, broadcastMessage);
// }

void ClientReceiver::stop() {
    isRunning = false;
}

bool ClientReceiver::getIsRunning() {
    return isRunning;
}
