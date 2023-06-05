#include "client_receiver.h"

#include <string>

ClientReceiver::ClientReceiver(Socket &clientSocket, GamesManager &gamesManager, 
                            Queue<ServerMessage> &gameResponses)
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
            int tipo_comando = protocol.receive_type_of_command(was_closed, clientSocket);
            std::cout << "SE RECIBE TIPO DE COMANDO\n";
            if (was_closed) {
                return;
            }

            if (tipo_comando == CREATE){
                std::cout << "SE RECIBE CREATE\n";
                std::string name_scenario = protocol.receive_create(was_closed, clientSocket);
                if (was_closed) {
                    break;
                }
                handleCreateAction();
                //const int code_game = game->getCode();
                //protocol.notify_create(code_game, clientSocket, was_closed);
                //std::cout << "Created match: " << code_game << "\n";
            }

            if (tipo_comando == JOIN){
                const int code_game = protocol.receive_join(was_closed, clientSocket);
                if (was_closed) {
                    break;
                }
                handleJoinAction(code_game);
            }
            // clientSocket.recvall(&action, 1, &was_closed);
            std::string decoded_action = "create";  // Place holder you should get the value from protocol
            // std::string decoded_action = protocol.decodeAction(action);

            // Conection was interrupted
            // } else if (decoded_action == "broadcast") {
            //     handleBroadcastAction(clientSocket, was_closed);
            // } else {
            //     std::cerr << "Unknown action: " << static_cast<int>(action) << std::endl;
            // }

            /*    while (not was_closed) {
        int tipo_comando = protocol.receive_type_of_command(was_closed, clientSocket);
        if (was_closed) {
            return;
        }
        if (tipo_comando == CREATE){
            std::string name_scenario = protocol.receive_create(was_closed, clientSocket);
            game = gameManager.create(name_scenario, qClient, idPlayer);
            const int code_game = game->getCode();
            //protocol.notify_create(code_game, clientSocket, was_closed);
            std::cout << "Created match: " << code_game << "\n";
        }
        if (tipo_comando == START_GAME){
            qActions = gameManager.startGame(game->getCode());
            break;
        }
        if (tipo_comando == JOIN){
            idPlayer = 1;
            const int code_game = protocol.receive_join(was_closed, clientSocket); 
            //game = gameManager.join(code_game, qClient, idPlayer);
            qActions = gameManager.join(code_game, qClient, idPlayer);
            if (game == NULL){
                std::cout << "Match does not exist: 1\n";
                //protocol.notify_join(0, clientSocket, was_closed);
            } 
            if (game != NULL) {
                std::cout << "Joined to match: " << code_game << "\n";
                //protocol.notify_join(1, clientSocket, was_closed);
            }
            break;
        }
    }*/
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

void ClientReceiver::stop() {
    isRunning = false;
}

bool ClientReceiver::getIsRunning() {
    return isRunning;
}
