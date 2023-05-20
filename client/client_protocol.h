#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include "socket.h"
#include <string>
#include <vector>

#define CREATE 1
#define JOIN 2
#define MOVE 3
#define SEND_MSG 4

class ClientProtocol {
 private:
    const std::string hostname;
    Socket skt;

 public:
    explicit ClientProtocol(const std::string& hostname, const std::string& servname);

    // ENVIA

    void create(const std::string& scenario, bool& was_closed);

    void join(int code, bool& was_closed);

    void move(uint32_t difx, uint32_t dify, bool& was_closed);

    // RECIBE

    std::string read(bool& was_closed);

    bool receive_notification_join(bool& was_closed);

    uint32_t receive_notification_create(bool& was_closed);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
