#include "client_receiver.h"

#include <string>

ClientReceiver::ClientReceiver(Socket &clientSocket, GamesManager &gamesManager, Queue<ServerMessage> &gameResponses)
    : clientSocket(clientSocket),
      gamesManager(gamesManager),
      game(nullptr),
      playerId(""),
      isRunning(false),
      gameResponses(gameResponses),
      protocol() {}

void ClientReceiver::run() {
    std::cout << "ENTRA AL RECEIVER\n";
    isRunning = true;
    try {
        while (isRunning) {
            // uint8_t action;
            bool was_closed = false;
            // clientSocket.recvall(&action, 1, &was_closed);
            std::string decoded_action = "create";  // Place holder you should get the value from protocol
            // std::string decoded_action = protocol.decodeAction(action);

            // Conection was interrupted
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

void ClientReceiver::handleCreateAction() {
    GameRecord gameRecord = gamesManager.createLobby(gameResponses);
    game = gameRecord.game;
    playerId = gameRecord.playerId;
    // std::cout << "Created match: " << newGameCode << std::endl;

    // std::vector<uint8_t> createResponse = protocol.encodeCreateResponse(newGameCode);
    // queue.push(createResponse);
}

void ClientReceiver::handleJoinAction(const int code) {
    GameRecord gameRecord = gamesManager.joinLobby(code, gameResponses);
    if (gameRecord.game != nullptr) {
        game = gameRecord.game;
        playerId = gameRecord.playerId;
        // std::cout << "Joined to match: " << code << std::endl;
    } else {
        // std::cout << "Match does not exist: " << code << std::endl;
        return;  // Return early as no more work can be done if the lobby doesn't exist
    }
    // std::vector<uint8_t> joinResponse = protocol.encodeJoinResponse(joinSuccess);
    // queue.push(joinResponse);
}

void ClientReceiver::handleGameAction() {
    // We can move this to line 32
    // int actionType = protocol.receiveActionType(clientSocket, was_closed);
    // TODO: check if number of actionType is between the accepted range to create action
    int movementType = 0;  // placeholder you should get the action from the protocol
    int directionXType = 0;
    int directionYType = 0;
    Action action(playerId, movementType, directionXType, directionYType);
    game->pushAction(action);
}

void ClientReceiver::stop() {
    isRunning = false;
}

bool ClientReceiver::getIsRunning() {
    return isRunning;
}
