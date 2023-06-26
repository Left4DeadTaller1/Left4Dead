#include "client_receiver.h"

#include <iostream>
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
            int typeCommand;

            try {
                typeCommand = protocol.receiveTypeCommand(wasClosed, clientSocket);
                std::cout << "type command: " << typeCommand << "\n";
            } catch (const std::runtime_error &e) {
                std::cerr << "Player disconnected: " << e.what() << std::endl;
                handlePlayerDisconnection();
                break;
            }

            int code;
            std::vector<int> data;
            infoCreate_t infoCreate;
            infoJoin_t infoJoin;

            switch (typeCommand) {
                case CREATE:
                    std::cout << "SE RECIBE CREATE CON:\n";
                    infoCreate = protocol.receiveCreate(wasClosed, clientSocket);
                    std::cout << "typeWeapon: " << (int)infoCreate.typeWeapon << "\n";
                    std::cout << "typeMap: " << (int)infoCreate.typeMap << "\n";
                    std::cout << "nickname: " << infoCreate.nickname << "\n";
                    if (!game)
                        handleCreateAction();
                    break;
                case JOIN:
                    std::cout << "SE RECIBE JOIN CON:\n";
                    infoJoin = protocol.receiveJoin(wasClosed, clientSocket);
                    std::cout << "typeWeapon: " << (int)infoJoin.typeWeapon << "\n";
                    std::cout << "code: " << (int)infoJoin.code << "\n";
                    std::cout << "nickname: " << infoJoin.nickname << "\n";
                    if (!game->isGameRunning())
                        handleJoinAction(infoJoin.code);
                    break;
                case START_GAME:
                    std::cout << "SE RECIBE START\n";
                    // TODO receive the gameCode and pass it to the startGame
                    if (!game->isGameRunning())
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
    Action action(playerId, 3, 3, 3);
    game->pushAction(action);
}

void ClientReceiver::handleEndShoot() {
    Action action(playerId, 2, 3, 3);
    game->pushAction(action);
}

void ClientReceiver::handleRecharge() {
    Action action(playerId, 4, 3, 3);
    game->pushAction(action);
}

void ClientReceiver::handleStartMove(int movementType, int directionXType, int directionYType) {
    Action action(playerId, movementType, directionXType, directionYType);
    game->pushAction(action);
}

void ClientReceiver::handleEndMove(int directionXType, int directionYType) {
    int movementType = 6;
    Action action(playerId, movementType, directionXType, directionYType);
    game->pushAction(action);
}

// TODO prob remove this
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

void ClientReceiver::handlePlayerDisconnection() {
    game->removePlayer(gameResponses);
    Action action(playerId, 7, 2, 2);
    game->pushAction(action);
}