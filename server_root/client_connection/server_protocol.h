#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "action.h"
#include "entity.h"
#include "player.h"
#include "server_message.h"
#include "socket.h"
#include "zombie.h"


typedef enum {
    CREATE,
    JOIN,
    START_GAME,
    START_MOVE,
    END_MOVE,
    START_SHOOT,
    END_SHOOT,
    RECHARGE,
    EXIT
} Type;

enum class GeneralState {
    WALKING,
    RUNNING,
    WALKING_SHOOTING,
    RUNNING_SHOOTING,
    SHOOTING,
    RELOADING,
    HURT,
    DEAD,
    IDLE
};

class ServerProtocol {
    public:
    ServerProtocol(void);

    int receiveTypeCommand(bool &wasClosed, Socket &peer);

    std::string receiveCreate(bool &wasClosed, Socket &peer);

    uint8_t receiveJoin(bool &wasClosed, Socket &peer);

    void notifyCreate(uint32_t code, Socket &peer, bool &wasClosed);

    std::vector<int> receiveStartMove(bool& wasClosed, Socket &peer);

    std::vector<int> receiveEndMove(bool& wasClosed, Socket &peer);

    ServerProtocol(const ServerProtocol &) = delete;
    ServerProtocol &operator=(const ServerProtocol &) = delete;

    ServerProtocol(ServerProtocol &&) = default;
    ServerProtocol &operator=(ServerProtocol &&) = default;

    // Just my things here:
    std::vector<uint8_t> encodeServerMessage(std::string msgType, const std::vector<std::shared_ptr<EntityDTO>> &entities);
    // ServerMessage decodeServerMessage(const std::vector<uint8_t> &encodedMsg);
    GeneralState determineGeneralState(const std::shared_ptr<EntityDTO> &entity);
    std::vector<uint8_t> encodeServerMessage(const std::string &msgType, const std::string &playerId);
    std::vector<uint8_t> encodeServerMessage(const std::string &msgType, bool serverResponse);
};

#endif