#include "server_protocol.h"

#include <arpa/inet.h>

#include <iostream>

/*ServerProtocol::ServerProtocol(const std::string& servname) :
    servname(servname){}*/

ServerProtocol::ServerProtocol(void) {}

void ServerProtocol::notify_create(uint32_t code, Socket &peer, bool &was_closed) {
    uint32_t buf_code[1];
    buf_code[0] = htonl(code);
    peer.sendall(buf_code, 4, &was_closed);
}

void ServerProtocol::notify_join(uint8_t param, Socket &peer, bool &was_closed) {
    uint8_t id[1];
    id[0] = param;
    peer.sendsome(id, 1, &was_closed);
}

void ServerProtocol::send_update_move(uint32_t posx, uint32_t posy, bool &was_closed, Socket &peer) {
    uint32_t buf_posx[1];
    buf_posx[0] = posx;
    buf_posx[0] = htonl((uint32_t)buf_posx[0]);
    peer.sendall(buf_posx, 4, &was_closed);
    if (was_closed)
        return;

    uint32_t buf_posy[1];
    buf_posy[0] = posy;
    buf_posy[0] = htonl((uint32_t)buf_posy[0]);
    peer.sendall(buf_posy, 4, &was_closed);
}

int ServerProtocol::receive_type_of_command(bool &was_closed, Socket &peer) {
    uint8_t buf[1];
    peer.recvsome(buf, 1, &was_closed);

    return (int)buf[0];
}

std::string ServerProtocol::receive_create(bool &was_closed, Socket &peer) {
    uint16_t buf_scenario_len[1];
    peer.recvall(buf_scenario_len, 2, &was_closed);
    uint16_t scenario_len = ntohs(buf_scenario_len[0]);

    char buf_scenario_name[100];  // despues ver cual es el max, creo que esta def
    peer.recvall(buf_scenario_name, scenario_len, &was_closed);
    buf_scenario_name[scenario_len] = '\0';

    return buf_scenario_name;
}

uint32_t ServerProtocol::receive_join(bool &was_closed, Socket &peer) {
    uint32_t buf_code[1];
    peer.recvall(buf_code, 4, &was_closed);
    uint32_t code = ntohl(buf_code[0]);

    return code;
}

std::vector<int> ServerProtocol::receive_start_move(bool &was_closed, Socket &peer) {
    std::vector<int> vector;

    uint32_t buf_difx[1];
    peer.recvall(buf_difx, 4, &was_closed);
    vector.push_back(ntohl(buf_difx[0]));

    uint32_t buf_dify[1];
    peer.recvall(buf_dify, 4, &was_closed);
    vector.push_back(ntohl(buf_dify[0]));

    return vector;
}

std::vector<uint8_t> ServerProtocol::encodeServerMessage(std::string msgType, const std::vector<std::shared_ptr<EntityDTO>> &entities) {
    uint8_t encodedMessageType = 1;

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
