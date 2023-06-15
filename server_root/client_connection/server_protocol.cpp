#include "server_protocol.h"

#include <arpa/inet.h>

#include <iostream>
#include <sstream>

ServerProtocol::ServerProtocol(void) {}

int ServerProtocol::receiveTypeCommand(bool &wasClosed, Socket &peer) {
    uint8_t type;
    peer.recvsome(&type, 1, &wasClosed);
    return type;
}

std::string ServerProtocol::receiveCreate(bool &wasClosed, Socket &peer) {
    uint8_t scenario_len;
    peer.recvall(&scenario_len, 1, &wasClosed);

    char buf_scenario_name[500];
    peer.recvall(buf_scenario_name, scenario_len, &wasClosed);
    buf_scenario_name[scenario_len] = '\0';

    return buf_scenario_name;
}

uint8_t ServerProtocol::receiveJoin(bool &wasClosed, Socket &peer) {
    uint8_t code;
    peer.recvall(&code, 1, &wasClosed);
    return code;
}

std::vector<int> ServerProtocol::receiveStartMove(bool &wasClosed, Socket &peer) {
    std::vector<int> vector;

    uint8_t typeMove;
    peer.recvall(&typeMove, 1, &wasClosed);
    vector.push_back(typeMove);

    int8_t x;
    peer.recvall(&x, 1, &wasClosed);
    vector.push_back(x);

    int8_t y;
    peer.recvall(&y, 1, &wasClosed);
    vector.push_back(y);

    return vector;
}

std::vector<int> ServerProtocol::receiveEndMove(bool &wasClosed, Socket &peer) {
    std::vector<int> vector;

    int8_t x;
    peer.recvall(&x, 1, &wasClosed);
    vector.push_back(x);

    int8_t y;
    peer.recvall(&y, 1, &wasClosed);
    vector.push_back(y);

    return vector;
}

std::shared_ptr<std::vector<uint8_t>> ServerProtocol::encodeServerMessage(std::string msgType, const std::vector<std::shared_ptr<EntityDTO>> &entities) {
    /*std::cout << "EN EL PROTOCOLO RECIBE\n";
    std::cout << "tipo de mensaje: " << msgType << "\n";
    std::cout << "cant entidadees izq: " << (int)entities.size() << "\n";
    std::cout << "tipo de entidad: " << (int)(entities[0]->type) << "\n";
    std::cout << "id entidad izq: " << (entities[0]->id) << "\n";
    std::cout << "estado mov entidad: " << (int)(entities[0]->movementDirectionX) << "\n";
    std::cout << "x: " << (int)(entities[0]->x) << "\n";
    std::cout << "y: " << (int)(entities[0]->y) << "\n";*/

    auto encodedMsg = std::make_shared<std::vector<uint8_t>>();

    uint8_t encodedMessageType = 1;
    // Adding the message type (1 byte)
    encodedMsg->push_back(encodedMessageType);

    // Adding the number of entities (2 bytes)
    uint16_t entitiesAmount = htons(static_cast<uint16_t>(entities.size()));
    encodedMsg->push_back(reinterpret_cast<uint8_t *>(&entitiesAmount)[0]);
    encodedMsg->push_back(reinterpret_cast<uint8_t *>(&entitiesAmount)[1]);

    for (const auto &entity : entities) {
        // Encode and add the entity type (1 byte)
        encodedMsg->push_back(static_cast<uint8_t>(entity->type));

        // Extract, convert, and add the entity id (2 bytes)
        std::string idNumberStr = extractId(entity->id);
        uint16_t id = htons(static_cast<uint16_t>(std::stoi(idNumberStr)));
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&id)[0]);
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&id)[1]);

        // Encode and add the general state (1 byte)
        GeneralState generalState = determineGeneralState(entity);
        encodedMsg->push_back(static_cast<uint8_t>(generalState));

        // Encode and add the X position (2 bytes)
        uint16_t encodedXPosition = htons(static_cast<uint16_t>(entity->x));
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedXPosition)[0]);
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedXPosition)[1]);

        // Encode and add the Y position (2 bytes)
        uint16_t encodedYPosition = htons(static_cast<uint16_t>(entity->y));
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedYPosition)[0]);
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedYPosition)[1]);

        // Encode and add the X direction (2 bytes)
        uint16_t encodedXDirection = htons(static_cast<uint16_t>(entity->movementDirectionX));
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedXDirection)[0]);
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedXDirection)[1]);

        // If the entity is a player, add the facing direction (1 byte)
        if (entity->type == PLAYER) {
            auto playerEntity = std::dynamic_pointer_cast<PlayerDTO>(entity);
            if (playerEntity) {
                encodedMsg->push_back(static_cast<uint8_t>(playerEntity->facingDirection));
            }
        }

        // Encode and add the health (1 byte)
        encodedMsg->push_back(static_cast<uint8_t>(entity->health));

        // If the entity is a zombie, add the zombie type (1 byte)
        if (entity->type == ZOMBIE) {
            auto zombieEntity = std::dynamic_pointer_cast<ZombieDTO>(entity);
            if (zombieEntity) {
                encodedMsg->push_back(static_cast<uint8_t>(zombieEntity->zombieType));
            }
        }
    }

    /*std::cout << "EN EL PROTOCOLO\n";
    std::cout << "tipo de mensaje: " << (int)(*encodedMsg)[0] << "\n";
    std::cout << "cant entidadees izq: " << (int)(*encodedMsg)[1] << "\n";
    std::cout << "cant entidadees der: " << (int)(*encodedMsg)[2] << "\n";
    std::cout << "tipo de entidad: " << (int)(*encodedMsg)[3] << "\n";
    std::cout << "id entidad izq: " << (int)(*encodedMsg)[4] << "\n";
    std::cout << "id entidad der: " << (int)(*encodedMsg)[5] << "\n";
    std::cout << "estado mov entidad: " << (int)(*encodedMsg)[6] << "\n";
    std::cout << "x izq: " << (int)(*encodedMsg)[7] << "\n";
    std::cout << "x der: " << (int)(*encodedMsg)[8] << "\n";
    std::cout << "y izq: " << (int)(*encodedMsg)[9] << "\n";
    std::cout << "y der: " << (int)(*encodedMsg)[10] << "\n";*/

    return encodedMsg;
}

std::string ServerProtocol::extractId(const std::string &str) {
    std::string result;

    for (char c : str) {
        if (std::isdigit(c)) {
            result += c;
        }
    }

    return result;
}

GeneralState ServerProtocol::determineGeneralState(const std::shared_ptr<EntityDTO> &entity) {
    if (entity->healthState == HealthState::DEAD) {
        return GeneralState::DEAD;
    } else if (entity->healthState == HealthState::HURT) {
        return GeneralState::HURT;
    }

    if (entity->type == PLAYER) {
        std::shared_ptr<PlayerDTO> player = std::dynamic_pointer_cast<PlayerDTO>(entity);

        if (player->weaponState == WeaponState::SHOOTING) {
            if (entity->movementState == MovementState::ENTITY_WALKING) {
                return GeneralState::WALKING_SHOOTING;
            } else if (entity->movementState == MovementState::ENTITY_RUNNING) {
                return GeneralState::RUNNING_SHOOTING;
            } else {
                return GeneralState::SHOOTING;
            }
        } else if (player->weaponState == WeaponState::RELOADING) {
            return GeneralState::RELOADING;
        }
    }

    if (entity->movementState == MovementState::ENTITY_WALKING) {
        return GeneralState::WALKING;
    } else if (entity->movementState == MovementState::ENTITY_RUNNING) {
        return GeneralState::RUNNING;
    }

    return GeneralState::IDLE;
}

std::shared_ptr<std::vector<uint8_t>> ServerProtocol::encodeServerMessage(const std::string &msgType, const std::string &playerId) {
    std::shared_ptr<std::vector<uint8_t>> encodedMsg = std::make_shared<std::vector<uint8_t>>();

    if (msgType == "JoinMsg") {
        encodedMsg->push_back(2);

        // Extracting the number from the playerId string
        std::string idNumberStr = extractId(playerId);
        int id = std::stoi(idNumberStr);

        // Cast to uint8_t and add it to the encoded message
        encodedMsg->push_back(static_cast<uint8_t>(id));
    }

    return encodedMsg;
}

std::shared_ptr<std::vector<uint8_t>> ServerProtocol::encodeServerMessage(const std::string &msgType, bool serverResponse) {
    std::shared_ptr<std::vector<uint8_t>> encodedMsg = std::make_shared<std::vector<uint8_t>>();

    if (msgType == "JoinMsg") {
        encodedMsg->push_back(2);

        if (serverResponse) {
            encodedMsg->push_back(1);
            // TODO: maybe here also push the game code or something?
        } else {
            encodedMsg->push_back(0);
        }
    }

    return encodedMsg;
}

std::shared_ptr<std::vector<uint8_t>> ServerProtocol::encodeServerMessage() {
    // Yeah i know this method seems pointless i just need a msg to send to the clients to tell them the game started
    std::shared_ptr<std::vector<uint8_t>> encodedMsg = std::make_shared<std::vector<uint8_t>>();

    encodedMsg->push_back(3);

    return encodedMsg;
}
