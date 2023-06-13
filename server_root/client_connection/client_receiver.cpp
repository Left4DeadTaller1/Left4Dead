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
    std::cout << "ENTRA AL RECEIVER\n";
    isRunning = true;
    try {
        while (isRunning) {
            bool wasClosed = false;

            int tipoComando = protocol.receiveTypeCommand(wasClosed, clientSocket);
            int code;
            std::vector<int> data;

            switch (tipoComando) {
                case CREATE:
                    std::cout << "CREATE\n";
                    protocol.receiveCreate(wasClosed, clientSocket);
                    handleCreateAction();
                    break;
                case JOIN:
                    std::cout << "JOIN\n";
                    code = protocol.receiveJoin(wasClosed, clientSocket);
                    std::cout << "code: " << code << "\n";
                    handleJoinAction(code);
                    break;
                case START_GAME:
                    std::cout << "START_GAME\n";
                    gamesManager.startGame(0);
                    break;
                case START_MOVE:
                    data = protocol.receiveStartMove(wasClosed, clientSocket);
                    std::cout << "START_MOVE\n";
                    std::cout << "type: " << data[0] << "\n";
                    std::cout << "dirx: " << data[1] << "\n";
                    std::cout << "diry: " << data[2] << "\n";
                    handleStartMove(data[0], data[1], data[2]);
                    break;
                case END_MOVE:
                    data = protocol.receiveEndMove(wasClosed, clientSocket);
                    std::cout << "END_MOVE\n";
                    std::cout << "dirx: " << data[0] << "\n";
                    std::cout << "diry: " << data[1] << "\n";
                    handleEndMove(data[0], data[1]);
                    break;
                case START_SHOOT:
                    std::cout << "START_SHOOT\n";
                    handleStartShoot();
                    break;
                case END_SHOOT:
                    std::cout << "END_SHOOT\n";
                    handleEndShoot();
                    break;
                case RECHARGE:
                    std::cout << "RECHARGE\n";
                    handleRecharge();
                    break;
                    /*case EXIT:
                        break;*/
            }
            // uint8_t action;
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
        std::shared_ptr<std::vector<uint8_t>> joinMessage = protocol.encodeServerMessage("JoinMsg", false);
        gameResponses.push(joinMessage);
    }
    // std::vector<uint8_t> joinResponse = protocol.encodeJoinResponse(joinSuccess);
    // queue.push(joinResponse);
}

void ClientReceiver::handleStartShoot() {
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

/*
    while (not was_closed) {
        int tipo_comando_ = protocol.receiveTypeCommand(was_closed, peer);
        if (was_closed) {
            break;
        }
        if (tipo_comando_ == START_MOVE){
            std::vector<int> data = protocol.receiveStartMove(was_closed, peer);
            std::cout << "se recibe START_MOVE con: \n";
            std::cout << "type: " << data[0] << "\n";
            std::cout << "dirx: " << data[1] << "\n";
            std::cout << "diry: " << data[2] << "\n";
            if ((int)data[1] == 1 && (int)data[2] == 0 && (int)data[0] == 0){
                std::shared_ptr<Action> startMove = std::make_shared<StartMove>(WALK, RIGHT);
                qActions->push(startMove);
            }
        }
        if (tipo_comando_ == END_MOVE){
            std::vector<int> data = protocol.receiveEndMove(was_closed, peer);
            std::cout << "se recibe END_MOVE con: \n";
            std::cout << "dirx: " << data[0] << "\n";
            std::cout << "diry: " << data[1] << "\n";
            if ((int)data[0] == 1 && (int)data[1] == 0){
                std::shared_ptr<Action> endMove = std::make_shared<EndMove>(RIGHT);
                qActions->push(endMove);
            }
        }
        if (tipo_comando_ == START_SHOOT){
            std::cout << "se recibe START_SHOOT\n";
        }
        if (tipo_comando_ == END_SHOOT){
            std::cout << "se recibe END_SHOOT\n";
        }
        if (tipo_comando_ == RECHARGE){
            std::cout << "se recibe RECHARGE\n";
        }
    }*/
