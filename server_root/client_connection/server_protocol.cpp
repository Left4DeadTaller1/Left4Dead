#include "server_protocol.h"

#include <arpa/inet.h>

#include <iostream>

ServerProtocol::ServerProtocol(void) {}

int ServerProtocol::receiveTypeCommand(bool &wasClosed, Socket &peer){
    uint8_t type;
    peer.recvsome(&type, 1, &wasClosed);
    return type;
}

std::string ServerProtocol::receiveCreate(bool &wasClosed, Socket &peer){
    uint8_t scenario_len;
    peer.recvall(&scenario_len, 1, &wasClosed);

    char buf_scenario_name[500];
    peer.recvall(buf_scenario_name, scenario_len, &wasClosed);
    buf_scenario_name[scenario_len] = '\0';

    return buf_scenario_name;
}

uint8_t ServerProtocol::receiveJoin(bool &wasClosed, Socket &peer){
    uint8_t code;
    peer.recvall(&code, 1, &wasClosed);
    return code;
}

std::vector<int> ServerProtocol::receiveStartMove(bool& wasClosed, Socket &peer){
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

std::vector<int> ServerProtocol::receiveEndMove(bool& wasClosed, Socket &peer){
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
    uint8_t encodedMessageType = 9; // cambie (lari) solo para ver si se recibe un 9 al pricipio

    uint16_t msg_len = htons(static_cast<uint16_t>(entities.size()));
    std::vector<uint8_t> encodedMsg;

    encodedMsg.push_back(encodedMessageType);

    // Adding the number of entities (2 bytes)
    encodedMsg.resize(encodedMsg.size() + 2);
    *(uint16_t *)(encodedMsg.data() + 1) = msg_len;

    for (const auto &entity : entities) {
        // Encode type
        uint8_t encodedType = static_cast<uint8_t>(entity->type);
        encodedMsg.push_back(encodedType);

        // Extracting and converting the entity id
        std::string idNumberStr = entity->id.substr(entity->id.find_first_of("0123456789"));
        uint16_t id = std::stoi(idNumberStr);
        id = htons(id);

        // Adding the id (2 bytes)
        encodedMsg.resize(encodedMsg.size() + 2);
        *(uint16_t *)(encodedMsg.data() + encodedMsg.size() - 2) = id;

        // Encode general state
        GeneralState generalState = determineGeneralState(entity);
        uint8_t encodedGeneralState = static_cast<uint8_t>(generalState);

        // Adding the general state (1 byte)
        encodedMsg.push_back(encodedGeneralState);

        // Encode X position
        uint16_t encodedXPosition = htons(static_cast<uint16_t>(entity->x));

        // Adding the X position (2 bytes)
        encodedMsg.resize(encodedMsg.size() + 2);
        *(uint16_t *)(encodedMsg.data() + encodedMsg.size() - 2) = encodedXPosition;

        // Encode Y position
        uint16_t encodedYPosition = htons(static_cast<uint16_t>(entity->y));

        // Adding the Y position (2 bytes)
        encodedMsg.resize(encodedMsg.size() + 2);
        *(uint16_t *)(encodedMsg.data() + encodedMsg.size() - 2) = encodedYPosition;

        // Encode X direction TODO: change this to face direction
        uint16_t encodedXDirection = htons(static_cast<uint16_t>(entity->movementDirectionX));

        // Adding the X direction (2 bytes)
        encodedMsg.resize(encodedMsg.size() + 2);
        *(uint16_t *)(encodedMsg.data() + encodedMsg.size() - 2) = encodedXDirection;

        if (entity->type == PLAYER) {
            auto playerEntity = std::dynamic_pointer_cast<PlayerDTO>(entity);
            if (playerEntity) {
                uint8_t facingDirection = static_cast<uint8_t>(playerEntity->facingDirection);
                // Adding the facing direction of player (1 byte)
                encodedMsg.push_back(facingDirection);
            }
        }

        // Encode health
        uint8_t encodedHealth = static_cast<uint8_t>(entity->health);

        // Adding the health (1 byte)
        encodedMsg.push_back(encodedHealth);

        if (entity->type == ZOMBIE) {
            auto zombieEntity = std::dynamic_pointer_cast<ZombieDTO>(entity);
            if (zombieEntity) {
                uint8_t encodedZombieType = static_cast<uint8_t>(zombieEntity->zombieType);

                // Adding the zombie type (1 byte)
                encodedMsg.push_back(encodedZombieType);
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
