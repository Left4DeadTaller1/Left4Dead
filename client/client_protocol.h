#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <vector>

#include "socket.h"

#define CREATE 1
#define JOIN 2
#define MOVE 3
#define SEND_MSG 4

class ClientProtocol {
   private:
    Socket& skt;

   public:
    explicit ClientProtocol(Socket& skt);

    // ENVIA

    void create(const std::string& scenario, bool& was_closed);

    void join(int code, bool& was_closed);

    void move(uint32_t difx, uint32_t dify, bool& was_closed);

    // RECIBE

    std::string read(bool& was_closed);

    bool receiveNotificationJoin(bool& was_closed);

    uint32_t receive_notification_create(bool& was_closed);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
