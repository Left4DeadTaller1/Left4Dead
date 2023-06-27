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
            } catch (const std::runtime_error &e) {
                std::cerr << "Player disconnected: " << e.what() << std::endl;
                handlePlayerDisconnection();
                stop();
                break;
            }

            // std::vector<int> data;
            infoCreate_t infoCreate;
            infoJoin_t infoJoin;

            switch (typeCommand) {
                case CREATE: {
                    std::cout << "SE RECIBE CREATE CON:\n";
                    infoCreate = protocol.receiveCreate(wasClosed, clientSocket);
                    std::cout << "typeWeapon: " << (int)infoCreate.typeWeapon << "\n";
                    std::cout << "typeMap: " << (int)infoCreate.typeMap << "\n";
                    std::cout << "nickname: " << infoCreate.nickname << "\n";
                    if (!game) {
                        std::cout << "entered here" << std::endl;
                        handleCreateAction(infoCreate.nickname, infoCreate.typeWeapon, infoCreate.typeMap);
                    }
                    break;
                }
                case JOIN: {
                    if (!game) {
                        std::cout << "SE RECIBE JOIN CON:\n";
                        infoJoin = protocol.receiveJoin(wasClosed, clientSocket);
                        std::cout << "typeWeapon: " << (int)infoJoin.typeWeapon << "\n";
                        std::cout << "code: " << (int)infoJoin.code << "\n";
                        std::cout << "nickname: " << infoJoin.nickname << "\n";
                        handleJoinAction(infoJoin.code, infoJoin.nickname, infoJoin.typeWeapon);
                    }
                    break;
                }
                case START_GAME: {
                    std::cout << "SE RECIBE START\n";
                    // TODO receive the gameCode and pass it to the startGame
                    if (!game->isGameRunning())
                        gamesManager.startGame(0);
                    break;
                }
                case START_MOVE: {
                    std::vector<int> data = protocol.receiveStartMove(wasClosed, clientSocket);
                    handleStartMove(data[0], data[1], data[2]);
                    break;
                }
                case END_MOVE: {
                    std::vector<int> data = protocol.receiveEndMove(wasClosed, clientSocket);
                    handleEndMove(data[0], data[1]);
                    break;
                }
                case START_SHOOT: {
                    handleStartShoot();
                    break;
                }
                case END_SHOOT: {
                    handleEndShoot();
                    break;
                }
                case RECHARGE: {
                    handleRecharge();
                    break;
                }
                case REVIVE: {
                    handleRevive();
                    break;
                }
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
    std::cout << "out of run loop" << std::endl;
    isRunning = false;
}

void ClientReceiver::handleCreateAction(std::string nickName, int typeWeapon, int typeMap) {
    GameRecord gameRecord = gamesManager.createLobby(gameResponses, nickName, typeWeapon, typeMap);
    game = gameRecord.game;
    playerId = gameRecord.playerId;
    // std::cout << "Created match: " << newGameCode << std::endl;

    // std::vector<uint8_t> createResponse = protocol.encodeCreateResponse(newGameCode);
    // queue.push(createResponse);
}

void ClientReceiver::handleJoinAction(const int code, std::string playerNickname, int weaponType) {
    std::cout << "entra handleJoinAction\n";
    try {
        GameRecord gameRecord = gamesManager.joinLobby(code, gameResponses, playerNickname, weaponType);
        game = gameRecord.game;
        playerId = gameRecord.playerId;
    } catch (const std::out_of_range &e) {
        std::shared_ptr<std::vector<uint8_t>> joinMessage = protocol.encodeServerMessage("JoinLobbyFailed");
        gameResponses.push(joinMessage);
    }
}

void ClientReceiver::handleStartShoot() {
    if (isGameFinish())
        return;
    Action action(playerId, 3, 3, 3);
    game->pushAction(action);
}

void ClientReceiver::handleEndShoot() {
    if (isGameFinish())
        return;
    Action action(playerId, 2, 3, 3);
    game->pushAction(action);
}

void ClientReceiver::handleRecharge() {
    if (isGameFinish())
        return;
    Action action(playerId, 4, 3, 3);
    game->pushAction(action);
}

void ClientReceiver::handleStartMove(int movementType, int directionXType, int directionYType) {
    if (isGameFinish())
        return;
    Action action(playerId, movementType, directionXType, directionYType);
    game->pushAction(action);
}

void ClientReceiver::handleEndMove(int directionXType, int directionYType) {
    if (isGameFinish())
        return;
    int movementType = 7;
    Action action(playerId, movementType, directionXType, directionYType);
    game->pushAction(action);
}

void ClientReceiver::handleRevive() {
    if (isGameFinish())
        return;
    Action action(playerId, 6, 3, 3);
    game->pushAction(action);
}

void ClientReceiver::stop() {
    std::cout << "stop being call" << std::endl;
    isRunning = false;
}

bool ClientReceiver::getIsRunning() {
    return isRunning;
}

void ClientReceiver::handlePlayerDisconnection() {
    if (isGameFinish())
        return;
    // game->removePlayer(gameResponses);
    Action action(playerId, 8, 2, 2);
    game->pushAction(action);
}

bool ClientReceiver::isGameFinish() {
    if (game && !game->isGameRunning()) {
        game.reset();  // Reset the shared_ptr when game is not running
        stop();
        return true;
    }
    return false;
}
