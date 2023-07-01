#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <vector>
#include <memory>

#include "socket.h"
#include "action_client.h"
#include "../render/game/client_game_state.h"

#define MSG_JOIN 2
#define MSG_START 4
#define MSG_GAME_STATE 9
#define MSG_END_GAME 5

typedef struct infoPlayerDTO {
    int id;
    std::string nickname;
    TypeWeapon_t typeWeapon;
} infoPlayerDTO_t;

typedef struct infoGameDTO {
    uint8_t code;
    TypeMap_t typeMap;
    int amountPlayers;   
    std::vector<infoPlayerDTO_t> infoPlayers;
} infoGameDTO_t;

class ClientProtocol {
   private:
    Socket skt;

    typeEntity_t getTypePlayer(TypeWeapon_t typeWeapon);
    
   public:
    ClientProtocol(const std::string& hostname,const std::string& servname);

    void sendAction(std::shared_ptr<ActionClient> action, bool& wasClosed);

    std::shared_ptr<gameStateDTO_t> receiveStateGame(bool& was_closed);

    std::shared_ptr<infoGameDTO_t> receiveCreateorJoin(bool& wasClosed);

    int receiveTypeMessage(bool& wasClosed);

    std::shared_ptr<gameStateDTO_t> receiveEndGame(bool& wasClosed);

    void closeSocket();

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
