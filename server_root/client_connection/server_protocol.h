#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "socket.h"
#include <string>
#include <memory>
#include <vector>
#include "action.h"
#include "game.h"

typedef enum {
    CREATE,
    JOIN,
    START_GAME,
    START_MOVE,
    END_MOVE,
    START_SHOOT,
    END_SHOOT
} Type;

class ServerProtocol {
    public:
    ServerProtocol();

    int receiveTypeCommand(bool &wasClosed, Socket &peer);

    std::string receiveCreate(bool &wasClosed, Socket &peer);

    uint8_t receiveJoin(bool &wasClosed, Socket &peer);

    std::vector<int> receiveStartMove(bool& wasClosed, Socket &peer);

    std::vector<int> receiveEndMove(bool& wasClosed, Socket &peer);

    void notifyCreate(uint32_t code, Socket &peer, bool &wasClosed);

    void notifyJoin(uint8_t param, Socket &peer, bool &wasClosed);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;
};

#endif