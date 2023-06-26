#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <vector>
#include <memory>

#include "socket.h"
#include "action_client.h"
#include "../render/game/client_game_state.h"

#define MSG_CREATE 2
#define MSG_JOIN 2
#define MSG_START 3
#define MSG_GAME_STATE 9

typedef struct infoPlayerJoin {
    std::string nickname;
    TypeWeapon_t typeWeapon;
    TypeMap_t typeMap;
} infoPlayerJoin_t;

class ClientProtocol {
   private:
    Socket skt;
    
   public:
    ClientProtocol(const std::string& hostname,const std::string& servname);

    void sendAction(std::shared_ptr<ActionClient> action, bool& wasClosed);

    std::shared_ptr<gameStateDTO_t> receiveStateGame(bool& was_closed);

    infoPlayerJoin_t receiveJoin(bool& wasClosed);

    int receiveCreate(bool& wasClosed);

    int receiveTypeMessage(bool& wasClosed);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
