#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <vector>

#include "socket.h"
#include "action_client.h"
#include "action_create.h"
#include "action_start_move.h"
#include "action_end_move.h"
#include "action_join.h"
#include "../render/game/client_game_state.h"

#define MSG_CREATE 2
#define MSG_JOIN 2
#define MSG_EXIT 3
#define MSG_GAME_STATE 9

class ClientProtocol {
   private:
    Socket& skt;
    
   public:
    explicit ClientProtocol(Socket& skt);

    void sendAction(std::shared_ptr<ActionClient> action, bool& wasClosed);

    std::shared_ptr<gameStateDTO_t> receiveStateGame(bool& was_closed);

    int receiveCreateorJoin(bool& wasClosed);

    void receiveExit(bool& wasClosed);

    int receiveTypeCommand(bool& wasClosed);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
