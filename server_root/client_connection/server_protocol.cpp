#include "server_protocol.h"

#include <arpa/inet.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

ServerProtocol::ServerProtocol(void) {}

int ServerProtocol::receiveTypeCommand(bool &wasClosed, Socket &peer) {
    uint8_t type;
    if (peer.recvall(&type, 1, &wasClosed) == 0)
        throw std::runtime_error("Player disconnected");
    return type;
}

std::string ServerProtocol::receiveCreate(bool &wasClosed, Socket &peer) {
    uint8_t name_len;
    peer.recvall(&name_len, 1, &wasClosed);

    char buf_name[500];
    peer.recvall(buf_name, name_len, &wasClosed);
    buf_name[name_len] = '\0';

    return buf_name;
}

dataJoin_t ServerProtocol::receiveJoin(bool &wasClosed, Socket &peer) {
    dataJoin_t dataJoin;

    uint8_t code;
    peer.recvall(&code, 1, &wasClosed);
    dataJoin.code = code;

    uint8_t name_len;
    peer.recvall(&name_len, 1, &wasClosed);

    char buf_name[500];
    peer.recvall(buf_name, name_len, &wasClosed);
    buf_name[name_len] = '\0';
    dataJoin.namePlayer = buf_name;
    
    return dataJoin;
}

/*uint8_t ServerProtocol::receiveJoin(bool &wasClosed, Socket &peer) {
    uint8_t code;
    peer.recvall(&code, 1, &wasClosed);
    return code;
}*/

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
    auto encodedMsg = std::make_shared<std::vector<uint8_t>>();

    uint8_t encodedMessageType = 9;
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

        // If the entity is a zombie, add the zombie type (1 byte)
        if (entity->type == ZOMBIE) {
            auto zombieEntity = std::dynamic_pointer_cast<ZombieDTO>(entity);
            if (zombieEntity) {
                encodedMsg->push_back(static_cast<uint8_t>(zombieEntity->zombieType));
            }
        }

        // Encode and add the general state (1 byte)
        GeneralState generalState = determineGeneralState(entity);
        encodedMsg->push_back(static_cast<uint8_t>(generalState));

        // Encode and add the action counter (1 byte)
        encodedMsg->push_back(static_cast<uint8_t>(entity->actionCounter));

        // Encode and add the X position (2 bytes)
        uint16_t encodedXPosition = htons(static_cast<uint16_t>(entity->x));
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedXPosition)[0]);
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedXPosition)[1]);

        // Encode and add the Y position (2 bytes)
        uint16_t encodedYPosition = htons(static_cast<uint16_t>(entity->y));
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedYPosition)[0]);
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedYPosition)[1]);

        // Encode and add the facing direction (1 byte)
        uint8_t encodedFacingDirection = static_cast<uint8_t>(entity->facingDirection);
        encodedMsg->push_back(encodedFacingDirection);

        // Encode and add the health (2 byte)
        uint16_t encodedHealth = htons(static_cast<uint16_t>(entity->health));
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedHealth)[0]);
        encodedMsg->push_back(reinterpret_cast<uint8_t *>(&encodedHealth)[1]);
    }

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
    switch (entity->type) {
        case PLAYER: {
            std::shared_ptr<PlayerDTO> player = std::dynamic_pointer_cast<PlayerDTO>(entity);
            return determinePlayerState(player);
            break;
        }

        case ZOMBIE: {
            std::shared_ptr<ZombieDTO> zombie = std::dynamic_pointer_cast<ZombieDTO>(entity);
            return determineZombieState(zombie);
            break;
        }

        default:
            return GeneralState::WALKING;
            break;
    }
}

GeneralState ServerProtocol::determinePlayerState(const std::shared_ptr<PlayerDTO> &playerState) {
    switch (playerState->actionState) {
        case PLAYER_WALKING:
            return GeneralState::WALKING;
            break;
        case PLAYER_RUNNING:
            return GeneralState::RUNNING;
            break;
        case PLAYER_IDLE:
            return GeneralState::IDLE;
            break;
        case PLAYER_SHOOTING:
            return GeneralState::SHOOTING;
            break;
        case PLAYER_RELOADING:
            return GeneralState::RELOADING;
            break;
        case PLAYER_HURT:
            return GeneralState::HURT;
            break;
        case PLAYER_DYING:
            return GeneralState::DYING;
            break;
        case PLAYER_DEAD:
            return GeneralState::DEAD;
            break;
        default:
            return GeneralState::WALKING;
            break;
    }
}

GeneralState ServerProtocol::determineZombieState(const std::shared_ptr<ZombieDTO> &zombie) {
    switch (zombie->zombieType) {
        case INFECTED:
            return determineInfectedState(zombie);
            break;

        case JUMPER:
            return determineJumperState(zombie);
            break;

        case WITCH:
            return determineWitchState(zombie);
            break;

        case SPEAR:
            return determineSpearState(zombie);
            break;

        case VENOM:
            return determineVenomState(zombie);
            break;

        default:
            return GeneralState::WALKING;
            break;
    }
}

GeneralState ServerProtocol::determineInfectedState(const std::shared_ptr<ZombieDTO> &zombie) {
    std::shared_ptr<InfectedDTO> infected = std::dynamic_pointer_cast<InfectedDTO>(zombie);
    switch (infected->actionState) {
        case INFECTED_MOVING:
            return GeneralState::WALKING;
            break;
        case INFECTED_HURT:
            return GeneralState::HURT;
            break;
        case INFECTED_DYING:
            return GeneralState::DYING;
            break;
        case INFECTED_DEAD:
            return GeneralState::DEAD;
            break;
        case INFECTED_ATTACKING:
            return GeneralState::ATTACKING;
            break;
        case INFECTED_IDLE:
            return GeneralState::IDLE;
            break;
        default:
            return GeneralState::WALKING;
            break;
    }
}

GeneralState ServerProtocol::determineJumperState(const std::shared_ptr<ZombieDTO> &zombie) {
    std::shared_ptr<JumperDTO> jumper = std::dynamic_pointer_cast<JumperDTO>(zombie);
    switch (jumper->actionState) {
        case JUMPER_MOVING:
            return GeneralState::WALKING;
            break;
        case JUMPER_HURT:
            return GeneralState::HURT;
            break;
        case JUMPER_DYING:
            return GeneralState::DYING;
            break;
        case JUMPER_DEAD:
            return GeneralState::DEAD;
            break;
        case JUMPER_ATTACKING:
            return GeneralState::ATTACKING;
            break;
        case JUMPER_JUMPING:
            return GeneralState::JUMPING;
            break;
        case JUMPER_IDLE:
            return GeneralState::IDLE;
            break;
        default:
            return GeneralState::WALKING;
            break;
    }
}

GeneralState ServerProtocol::determineWitchState(const std::shared_ptr<ZombieDTO> &zombie) {
    std::shared_ptr<WitchDTO> witch = std::dynamic_pointer_cast<WitchDTO>(zombie);
    switch (witch->actionState) {
        case WITCH_MOVING:
            return GeneralState::WALKING;
            break;
        case WITCH_HURT:
            return GeneralState::HURT;
            break;
        case WITCH_DYING:
            return GeneralState::DYING;
            break;
        case WITCH_DEAD:
            return GeneralState::DEAD;
            break;
        case WITCH_ATTACKING:
            return GeneralState::ATTACKING;
            break;
        case WITCH_SHOUTING:
            return GeneralState::SCREAMING;
            break;
        case WITCH_IDLE:
            return GeneralState::IDLE;
            break;
        default:
            return GeneralState::WALKING;
            break;
    }
}

GeneralState ServerProtocol::determineSpearState(const std::shared_ptr<ZombieDTO> &zombie) {
    std::shared_ptr<SpearDTO> spear = std::dynamic_pointer_cast<SpearDTO>(zombie);
    switch (spear->actionState) {
        case SPEAR_MOVING:
            return GeneralState::WALKING;
            break;
        case SPEAR_HURT:
            return GeneralState::HURT;
            break;
        case SPEAR_DYING:
            return GeneralState::DYING;
            break;
        case SPEAR_DEAD:
            return GeneralState::DEAD;
            break;
        case SPEAR_ATTACKING:
            return GeneralState::ATTACKING;
            break;
        case SPEAR_IDLE:
            return GeneralState::IDLE;
            break;
        default:
            return GeneralState::WALKING;
            break;
    }
}

GeneralState ServerProtocol::determineVenomState(const std::shared_ptr<ZombieDTO> &zombie) {
    std::shared_ptr<VenomDTO> venom = std::dynamic_pointer_cast<VenomDTO>(zombie);
    switch (venom->actionState) {
        case VENOM_MOVING:
            return GeneralState::WALKING;
            break;
        case VENOM_HURT:
            return GeneralState::HURT;
            break;
        case VENOM_DYING:
            return GeneralState::DYING;
            break;
        case VENOM_DEAD:
            return GeneralState::DEAD;
            break;
        case VENOM_ATTACKING:
            return GeneralState::ATTACKING;
            break;
        case VENOM_SHOOTING:
            return GeneralState::SHOOTING;
            break;
        case VENOM_IDLE:
            return GeneralState::IDLE;
            break;
        default:
            return GeneralState::WALKING;
            break;
    }
}

std::shared_ptr<std::vector<uint8_t>>
ServerProtocol::encodeServerMessage(const std::string &msgType, const std::string &playerId) {
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
    std::cout << "En el equivocado" << std::endl;
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
    std::cout << "En el equivocado 2" << std::endl;
    // Yeah i know this method seems pointless i just need a msg to send to the clients to tell them the game started
    std::shared_ptr<std::vector<uint8_t>> encodedMsg = std::make_shared<std::vector<uint8_t>>();

    encodedMsg->push_back(3);

    return encodedMsg;
}
