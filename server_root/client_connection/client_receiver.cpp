#include "client_receiver.h"

#include <string>

ClientReceiver::ClientReceiver(Socket &clientSocket, GamesManager &gamesManager, Queue<std::shared_ptr<std::vector<uint8_t>>> &gameResponses)
    : clientSocket(clientSocket),
      gamesManager(gamesManager),
      game(nullptr),
      playerId(""),
      isRunning(false),
      gameResponses(gameResponses),
      protocol() {}

void ClientReceiver::run() {
    isRunning = true;
    try {
        while (isRunning) {
            bool wasClosed = false;

            int tipoComando = protocol.receiveTypeCommand(wasClosed, clientSocket);
            int code;
            std::vector<int> data;
            dataJoin_t dataJoin;

            switch (tipoComando) {
                case CREATE:
                    protocol.receiveCreate(wasClosed, clientSocket);
                    handleCreateAction();
                    break;
                case JOIN:
                    dataJoin = protocol.receiveJoin(wasClosed, clientSocket);
                    std::cout << "code: " << dataJoin.code << "\n";
                    handleJoinAction(dataJoin.code);
                    break;
                case START_GAME:
                    gamesManager.startGame(0);
                    break;
                case START_MOVE:
                    data = protocol.receiveStartMove(wasClosed, clientSocket);
                    handleStartMove(data[0], data[1], data[2]);
                    break;
                case END_MOVE:
                    data = protocol.receiveEndMove(wasClosed, clientSocket);
                    handleEndMove(data[0], data[1]);
                    break;
                case START_SHOOT:
                    handleStartShoot();
                    break;
                case END_SHOOT:
                    handleEndShoot();
                    break;
                case RECHARGE:
                    handleRecharge();
                    break;
                    /*case EXIT:
                        break;*/
            }
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
    try {
        GameRecord gameRecord = gamesManager.joinLobby(code, gameResponses);
        game = gameRecord.game;
        playerId = gameRecord.playerId;
    } catch (const std::out_of_range &e) {
        std::shared_ptr<std::vector<uint8_t>> joinMessage = protocol.encodeServerMessage("JoinMsg", false);
        gameResponses.push(joinMessage);
    }
}

void ClientReceiver::handleStartShoot() {
    //std::cout << "entra handleStartShoot en receiver\n";
    Action action(playerId, 3, 3, 3, 0);
    game->pushAction(action);
}

void ClientReceiver::handleEndShoot() {
    Action action(playerId, 3, 3, 3, 2);
    game->pushAction(action);
}

void ClientReceiver::handleRecharge() {
    Action action(playerId, 3, 3, 3, 1);
    game->pushAction(action);
}

void ClientReceiver::handleStartMove(int movementType, int directionXType, int directionYType) {
    int weaponType = 3;
    Action action(playerId, movementType, directionXType, directionYType, weaponType);
    game->pushAction(action);
}

void ClientReceiver::handleEndMove(int directionXType, int directionYType) {
    int weaponType = 3;
    int movementType;
    if (directionXType == 2 && directionYType == 2) {
        movementType = 3;
        Action action(playerId, movementType, directionXType, directionYType, weaponType);
        game->pushAction(action);
        return;
    }
    movementType = 3;
    Action action(playerId, movementType, directionXType, directionYType, weaponType);
    game->pushAction(action);
}

void ClientReceiver::handleGameAction() {
    // We can move this to line 32
    // int actionType = protocol.receiveActionType(clientSocket, was_closed);
    // TODO: check if number of actionType is between the accepted range to create action
    int movementType = 0;  // placeholder you should get the action from the protocol
    int directionXType = 0;
    int directionYType = 0;
    int weaponType = 0;
    Action action(playerId, movementType, directionXType, directionYType, weaponType);
    game->pushAction(action);
}

void ClientReceiver::stop() {
    isRunning = false;
}

bool ClientReceiver::getIsRunning() {
    return isRunning;
}

