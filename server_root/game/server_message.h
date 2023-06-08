#ifndef SERVER_MESSAGE_H_
#define SERVER_MESSAGE_H_

#include <string>
#include <vector>

class ServerMessage {
   private:
    std::string messageType;
    std::vector<uint8_t> message;

   public:
    ServerMessage() = default;
    ServerMessage(std::string messageType, const std::vector<uint8_t>& message);
    std::string getMessageType() const;
    void setMessageType(const std::string& messageType);
    std::vector<uint8_t> getMessage() const;
    void setMessage(const std::vector<uint8_t>& message);
    ~ServerMessage();
};

#endif  // SERVER_MESSAGE_H_
