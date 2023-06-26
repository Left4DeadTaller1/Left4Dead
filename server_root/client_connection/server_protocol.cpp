#include "server_protocol.h"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <iomanip>
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

infoCreate_t ServerProtocol::receiveCreate(bool &wasClosed, Socket &peer) {
    // despues modificar como lo puso reg
    infoCreate_t info;

    uint8_t typeWeapon;
    peer.recvall(&typeWeapon, 1, &wasClosed);
    info.typeWeapon = static_cast<TypeWeapon_t>(typeWeapon);

    uint8_t typeMap;
    peer.recvall(&typeMap, 1, &wasClosed);
    info.typeMap = static_cast<TypeMap_t>(typeMap);

    uint8_t name_len;
    peer.recvall(&name_len, 1, &wasClosed);

    char buf_name[500];
    peer.recvall(buf_name, name_len, &wasClosed);
    buf_name[name_len] = '\0';
    info.nickname = buf_name;

    return info;
}

infoJoin_t ServerProtocol::receiveJoin(bool &wasClosed, Socket &peer) {
    infoJoin_t info;

    uint8_t code;
    peer.recvall(&code, 1, &wasClosed);
    info.code = code;

    uint8_t typeWeapon;
    peer.recvall(&typeWeapon, 1, &wasClosed);
    info.typeWeapon = static_cast<TypeWeapon_t>(typeWeapon);

    uint8_t name_len;
    peer.recvall(&name_len, 1, &wasClosed);

    char buf_name[500];
    peer.recvall(buf_name, name_len, &wasClosed);
    buf_name[name_len] = '\0';
    info.nickname = buf_name;

    return info;
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

        if (entity->type == PLAYER) {
            auto playerEntity = std::dynamic_pointer_cast<PlayerDTO>(entity);
            if (playerEntity) {
                std::string nickName = playerEntity->nickName;
                // Encode length of nickName (1 byte), and nickName (in len(nickName) bytes)
                encodePlayerNickName(encodedMsg, nickName);
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

    // std::cout << "Encoded Message: ";

    // int byteCount = 0;
    // int entityByteCount = -3;  // Exclude the first 3 bytes for counting bytes in entities
    // for (auto byte : *encodedMsg) {
    //     byteCount++;
    //     entityByteCount++;

    //     // Add separator after the first 3 bytes
    //     if (byteCount == 4) {
    //         std::cout << "| ";
    //     }

    //     // Add separator between entities (after every 13 bytes for zombies, excluding the first 3 bytes)
    //     if (byteCount > 4 && entityByteCount % 13 == 0) {
    //         std::cout << "| ";
    //     }

    //     // Color the 4th byte of zombies red and the 3rd byte blue
    //     if (byteCount > 4) {
    //         if (entityByteCount % 13 == 3) {
    //             std::cout << blueText;
    //         } else if (entityByteCount % 13 == 4) {
    //             std::cout << redText;
    //         }
    //     }

    //     // Print byte in decimal
    //     std::cout << static_cast<int>(byte) << " ";
    // }
    // std::cout << std::endl;

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
        case PLAYER_ATTACKING:
            return GeneralState::ATTACKING;
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

void ServerProtocol::encodePlayerNickName(std::shared_ptr<std::vector<uint8_t>> &encodedMsg, const std::string &nickName) {
    // Encode and add the length of the nickname (1 byte)
    uint8_t nickName_len = static_cast<uint8_t>(nickName.size());
    encodedMsg->push_back(nickName_len);

    // Encode and add the nickname
    encodedMsg->insert(encodedMsg->end(), nickName.begin(), nickName.end());
}

std::shared_ptr<std::vector<uint8_t>>
ServerProtocol::encodeServerMessage(const std::string &msgType, int typeMap, std::vector<LobbyPlayerDTO> &playersInfo) {
    std::shared_ptr<std::vector<uint8_t>> encodedMsg = std::make_shared<std::vector<uint8_t>>();

    if (msgType == "JoinLobby") {
        encodedMsg->push_back(2);

        // Adding the map type (1 byte)
        encodedMsg->push_back(static_cast<uint8_t>(typeMap));

        // Adding the amount of players (1 byte)
        encodedMsg->push_back(static_cast<uint8_t>(playersInfo.size()));

        for (const auto &player : playersInfo) {
            // Extracting the number from the playerId string
            std::string idNumberStr = extractId(player.id);
            int id = std::stoi(idNumberStr);
            // Cast to uint8_t and add it to the encoded message (1 byte)
            encodedMsg->push_back(static_cast<uint8_t>(id));

            std::string nickName = player.nickName;
            // Encode length of nickName (1 byte), and nickName (in len(nickName) bytes)
            encodePlayerNickName(encodedMsg, nickName);

            // Adding the weapon type (1 byte)
            encodedMsg->push_back(static_cast<uint8_t>(player.weaponType));
        }
    }

    return encodedMsg;
}

std::shared_ptr<std::vector<uint8_t>> ServerProtocol::encodeServerMessage(const std::string &msgType) {
    std::shared_ptr<std::vector<uint8_t>> encodedMsg = std::make_shared<std::vector<uint8_t>>();
    if (msgType == "JoinLobbyFailed") {
        encodedMsg->push_back(3);
    }

    if (msgType == "GameStarted") {
        encodedMsg->push_back(4);
    }

    return encodedMsg;
}
