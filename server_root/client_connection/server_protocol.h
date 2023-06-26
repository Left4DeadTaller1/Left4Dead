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

typedef enum : int8_t {
    WEAPON1,
    WEAPON2,
    WEAPON3
} TypeWeapon_t;

typedef enum : int8_t {
    MAP1,
    MAP2,
    MAP3,
    MAP4
} TypeMap_t;


typedef struct infoCreate {
    TypeWeapon_t typeWeapon;
    TypeMap_t typeMap;
    std::string nickname;
} infoCreate_t;

typedef struct infoJoin {
    int8_t code;
    TypeWeapon_t typeWeapon;
    std::string nickname;
} infoJoin_t;

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
    SCREAMING,         // 7
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

    infoCreate_t receiveCreate(bool &wasClosed, Socket &peer);

    infoJoin_t receiveJoin(bool &wasClosed, Socket &peer);

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
    void encodePlayerNickName(std::shared_ptr<std::vector<uint8_t>> &encodedMsg, const std::string &nickName);

    std::shared_ptr<std::vector<uint8_t>> encodeServerMessage(const std::string &msgType, int typeMap, std::vector<LobbyPlayerDTO> &playersInfo);
    std::shared_ptr<std::vector<uint8_t>> encodeServerMessage(const std::string &msgType);
};

#endif