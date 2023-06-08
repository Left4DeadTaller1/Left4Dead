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
    END_SHOOT
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
   private:
    // const std::string servname;

    void send_int32(int32_t number, bool &was_closed, Socket &peer);

    void send_int8(int8_t number, bool &was_closed, Socket &peer);

   public:
    // explicit ServerProtocol(const std::string& servname);
    ServerProtocol(void);

    // ENVIA

    void notify_create(uint32_t code, Socket &peer, bool &was_closed);

    void notify_join(uint8_t param, Socket &peer, bool &was_closed);

    void send_update_move(uint32_t posx, uint32_t posy, bool &was_closed, Socket &peer);

    // RECIBE

    int receive_type_of_command(bool &was_closed, Socket &peer);

    std::string receive_create(bool &was_closed, Socket &peer);

    uint32_t receive_join(bool &was_closed, Socket &peer);

    std::vector<int> receive_start_move(bool &was_closed, Socket &peer);

    /*void send_update_game(std::shared_ptr<gameStateDTO_t> gameStateDTO,
                                        bool& was_closed,
                                        Socket &peer);*/

    // std::vector<int> receive_move(bool& was_closed, Socket &peer);

    ServerProtocol(const ServerProtocol &) = delete;
    ServerProtocol &operator=(const ServerProtocol &) = delete;

    ServerProtocol(ServerProtocol &&) = default;
    ServerProtocol &operator=(ServerProtocol &&) = default;

    // Just my things here:
    std::vector<uint8_t> encodeServerMessage(std::string msgType, const std::vector<std::shared_ptr<EntityDTO>> &entities);
    // ServerMessage decodeServerMessage(const std::vector<uint8_t> &encodedMsg);
    GeneralState determineGeneralState(const std::shared_ptr<EntityDTO> &entity);
};

#endif