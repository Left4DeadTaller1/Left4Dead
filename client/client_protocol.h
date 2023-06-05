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

//typedef enum state_t;

class ClientProtocol {
   private:
    Socket& skt;


    //int32_t receive_int32(bool& was_closed);

    //state_t receive_int8(bool& was_closed);

   public:
    explicit ClientProtocol(Socket& skt);

    // ENVIA

    void sendAction(actionDTO* dto, bool& wasClosed);

    void startMove(StartMoveDTO_t* dto, bool& was_closed);

    void endMove(EndMoveDTO_t* dto, bool& was_closed);

    void create(CreateDTO_t* dto, bool& was_closed);

    void join(JoinDTO_t* dto, bool& was_closed);

    void startGame(bool& was_closed);

    // RECIBE

    bool receiveNotificationJoin(bool& was_closed);

    uint32_t receive_notification_create(bool& was_closed);

    std::vector<int> receive_update_move(bool& was_closed);

    //std::shared_ptr<gameStateDTO_t> receive_update_game(bool& was_closed);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
