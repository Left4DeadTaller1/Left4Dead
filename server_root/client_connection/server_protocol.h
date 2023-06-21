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
#include "infected.h"
#include "jumper.h"
#include "player.h"
#include "server_message.h"
#include "socket.h"
#include "spear.h"
#include "venom.h"
#include "witch.h"
#include "zombie.h"

typedef struct dataJoin {
    uint8_t code;
    std::string namePlayer;  
} dataJoin_t;

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
    WALKING,           // 0
    RUNNING,           // 1
    WALKING_SHOOTING,  // 2
    RUNNING_SHOOTING,  // 3
    SHOOTING,          // 4
    ATTACKING,         // 5
    JUMPING,           // 6
    SHOUTING,          // 7
    RELOADING,         // 8
    HURT,              // 9
    DYING,             // 10
    DEAD,              // 11
    IDLE               // 12
};

class ServerProtocol {
   public:
    ServerProtocol(void);

    int receiveTypeCommand(bool &wasClosed, Socket &peer);

    std::string receiveCreate(bool &wasClosed, Socket &peer);

    dataJoin_t receiveJoin(bool &wasClosed, Socket &peer);

    void notifyCreate(uint32_t code, Socket &peer, bool &wasClosed);

    std::vector<int> receiveStartMove(bool &wasClosed, Socket &peer);

    std::vector<int> receiveEndMove(bool &wasClosed, Socket &peer);

    ServerProtocol(const ServerProtocol &) = delete;
    ServerProtocol &operator=(const ServerProtocol &) = delete;

    ServerProtocol(ServerProtocol &&) = default;
    ServerProtocol &operator=(ServerProtocol &&) = default;

    // Just my things here:
    std::shared_ptr<std::vector<uint8_t>> encodeServerMessage(std::string msgType, const std::vector<std::shared_ptr<EntityDTO>> &entities);
    std::string extractId(const std::string &str);
    // ServerMessage decodeServerMessage(const std::vector<uint8_t> &encodedMsg);
    GeneralState determineGeneralState(const std::shared_ptr<EntityDTO> &entity);
    GeneralState determinePlayerState(const std::shared_ptr<PlayerDTO> &player);
    GeneralState determineZombieState(const std::shared_ptr<ZombieDTO> &zombie);

    GeneralState determineInfectedState(const std::shared_ptr<ZombieDTO> &zombie);
    GeneralState determineJumperState(const std::shared_ptr<ZombieDTO> &zombie);
    GeneralState determineWitchState(const std::shared_ptr<ZombieDTO> &zombie);
    GeneralState determineSpearState(const std::shared_ptr<ZombieDTO> &zombie);
    GeneralState determineVenomState(const std::shared_ptr<ZombieDTO> &zombie);

    std::shared_ptr<std::vector<uint8_t>> encodeServerMessage(const std::string &msgType, const std::string &playerId);
    std::shared_ptr<std::vector<uint8_t>> encodeServerMessage(const std::string &msgType, bool serverResponse);
    std::shared_ptr<std::vector<uint8_t>> encodeServerMessage();
};

#endif