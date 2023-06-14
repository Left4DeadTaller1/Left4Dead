#include "client_sender.h"

ClientSender::ClientSender(Socket &skt, Queue<std::shared_ptr<std::vector<uint8_t>>> &gameResponses)
    : clientSocket(skt),
      gameResponses(gameResponses),
      isRunning(false),
      protocol() {}

void ClientSender::menu() {}

void ClientSender::run() {
    isRunning = true;
    try {
        while (isRunning) {
            // Now gameSnapShot is a vector of bytes representing the game state
            std::shared_ptr<std::vector<uint8_t>> gameSnapShotPtr = gameResponses.pop();

            if (gameSnapShotPtr == nullptr) {
                // TODO: maybe add an error throw or smthing
                std::cout << "EN PUNTERO ES NULL\n";
                continue;
            }

            std::vector<uint8_t> gameSnapShot = *gameSnapShotPtr;

            bool was_closed = false;

            /*std::cout << "EN EL SENDER\n";
            std::cout << "tipo de mensaje: " << (int)gameSnapShot[0] << "\n";
            if ((int)gameSnapShot[0] == 9){
                std::cout << "size: " << gameSnapShot.size() << "\n";
                std::cout << "cant entidadees izq: " << (int)gameSnapShot[1] << "\n";
                std::cout << "cant entidadees der: " << (int)gameSnapShot[2] << "\n";

                std::cout << "tipo de entidad: " << (int)gameSnapShot[3] << "\n";
                std::cout << "id entidad izq: " << (int)gameSnapShot[4] << "\n";
                std::cout << "id entidad der: " << (int)gameSnapShot[5] << "\n";
                std::cout << "estado mov entidad: " << (int)gameSnapShot[6] << "\n";
                std::cout << "x izq: " << (int)gameSnapShot[7] << "\n";
                std::cout << "x der: " << (int)gameSnapShot[8] << "\n";
                std::cout << "y izq: " << (int)gameSnapShot[9] << "\n";
                std::cout << "y der: " << (int)gameSnapShot[10] << "\n";
                std::cout << "dir look izq : " << (int)gameSnapShot[11] << "\n";
                std::cout << "dir look der : " << (int)gameSnapShot[12] << "\n";
                std::cout << "face: " << (int)gameSnapShot[13] << "\n";
                std::cout << "health: " << (int)gameSnapShot[14] << "\n";

                std::cout << "tipo de entidad: " << (int)gameSnapShot[15] << "\n";
                std::cout << "id entidad izq: " << (int)gameSnapShot[16] << "\n";
                std::cout << "id entidad der: " << (int)gameSnapShot[17] << "\n";
                std::cout << "estado mov entidad: " << (int)gameSnapShot[18] << "\n";
                std::cout << "x izq: " << (int)gameSnapShot[19] << "\n";
                std::cout << "x der: " << (int)gameSnapShot[20] << "\n";
                std::cout << "y izq: " << (int)gameSnapShot[21] << "\n";
                std::cout << "y der: " << (int)gameSnapShot[22] << "\n";
                std::cout << "dir look izq : " << (int)gameSnapShot[23] << "\n";
                std::cout << "dir look der : " << (int)gameSnapShot[24] << "\n";
                std::cout << "face: " << (int)gameSnapShot[25] << "\n";
                std::cout << "health: " << (int)gameSnapShot[26] << "\n";
            }*/

            if (gameSnapShot.size() > 0) {
                clientSocket.sendall(gameSnapShot.data(), gameSnapShot.size(), &was_closed);
            }

            // Connection was interrupted
            if (was_closed) {
                break;
            }
        }
    } catch (const ClosedQueue &e) {
        // The queue is closed, end the thread
        std::cerr << "ClientSender: Queue is closed. Ending thread." << std::endl;
    } catch (const std::exception &e) {
        // Other standard exceptions
        std::cerr << "ClientSender: Exception caught: " << e.what() << std::endl;
    } catch (...) {
        // Other unknown exceptions
        std::cerr << "ClientSender: Unknown exception caught. Ending thread." << std::endl;
    }

    isRunning = false;
}

bool ClientSender::getIsRunning() {
    return isRunning;
}

void ClientSender::stop() {
    isRunning = false;
}

ClientSender::~ClientSender() {
    // Destructor implementation
}
