#include "server_protocol.h"

#include <arpa/inet.h>

#include <iostream>

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

std::vector<uint8_t> ServerProtocol::encodeServerMessage(std::string msgType, const std::vector<std::shared_ptr<EntityDTO>> &entities) {
    std::vector<uint8_t> encodedMsg;

    uint8_t encodedMessageType = 9;  // dummy value for example
    // Adding the message type (1 byte)
    encodedMsg.push_back(encodedMessageType);

    // Adding the number of entities (2 bytes)
    uint16_t entitiesAmount = htons(static_cast<uint16_t>(entities.size()));
    encodedMsg.push_back(reinterpret_cast<uint8_t *>(&entitiesAmount)[0]);
    encodedMsg.push_back(reinterpret_cast<uint8_t *>(&entitiesAmount)[1]);

    for (const auto &entity : entities) {
        // Encode and add the entity type (1 byte)
        encodedMsg.push_back(static_cast<uint8_t>(entity->type));

        // Extract, convert, and add the entity id (2 bytes)
        std::string idNumberStr = entity->id.substr(entity->id.find_first_of("0123456789"));
        uint16_t id = htons(static_cast<uint16_t>(std::stoi(idNumberStr)));
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&id)[0]);
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&id)[1]);

        // Encode and add the general state (1 byte)
        GeneralState generalState = determineGeneralState(entity);
        encodedMsg.push_back(static_cast<uint8_t>(generalState));

        // Encode and add the X position (2 bytes)
        uint16_t encodedXPosition = htons(static_cast<uint16_t>(entity->x));
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&encodedXPosition)[0]);
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&encodedXPosition)[1]);

        // Encode and add the Y position (2 bytes)
        uint16_t encodedYPosition = htons(static_cast<uint16_t>(entity->y));
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&encodedYPosition)[0]);
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&encodedYPosition)[1]);

        // Encode and add the X direction (2 bytes)
        uint16_t encodedXDirection = htons(static_cast<uint16_t>(entity->movementDirectionX));
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&encodedXDirection)[0]);
        encodedMsg.push_back(reinterpret_cast<uint8_t *>(&encodedXDirection)[1]);

        // If the entity is a player, add the facing direction (1 byte)
        if (entity->type == PLAYER) {
            auto playerEntity = std::dynamic_pointer_cast<PlayerDTO>(entity);
            if (playerEntity) {
                encodedMsg.push_back(static_cast<uint8_t>(playerEntity->facingDirection));
            }
        }

        // Encode and add the health (1 byte)
        encodedMsg.push_back(static_cast<uint8_t>(entity->health));

        // If the entity is a zombie, add the zombie type (1 byte)
        if (entity->type == ZOMBIE) {
            auto zombieEntity = std::dynamic_pointer_cast<ZombieDTO>(entity);
            if (zombieEntity) {
                encodedMsg.push_back(static_cast<uint8_t>(zombieEntity->zombieType));
            }
        }
    }

    return encodedMsg;
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

std::vector<uint8_t> ServerProtocol::encodeServerMessage(const std::string &msgType, const std::string &playerId) {
    std::vector<uint8_t> encodedMsg;

    if (msgType == "JoinMsg") {
        encodedMsg.push_back(2);

        // Extracting the number from the playerId string
        std::string idNumberStr = playerId.substr(playerId.find_first_of("0123456789"));
        int id = std::stoi(idNumberStr);

        // Cast to uint8_t and add it to the encoded message
        encodedMsg.push_back(static_cast<uint8_t>(id));
    }

    return encodedMsg;
}

std::vector<uint8_t> ServerProtocol::encodeServerMessage(const std::string &msgType, bool serverResponse) {
    std::vector<uint8_t> encodedMsg;

    if (msgType == "JoinMsg") {
        encodedMsg.push_back(2);

        if (serverResponse) {
            encodedMsg.push_back(1);
            // TODO: maybe here also push the game code or something?
        } else {
            encodedMsg.push_back(0);
        }
    }

    return encodedMsg;
}
