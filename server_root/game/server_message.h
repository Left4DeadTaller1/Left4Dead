#ifndef SERVER_MESSAGE_H_
#define SERVER_MESSAGE_H_

#include <string>

class ServerMessage {
   private:
    std::string messageType;
    std::string message;

   public:
    ServerMessage(std::string messageType, std::string message);
    std::string getMessageType() const;
    std::string getMessage() const;
    ~ServerMessage();
};

#endif  // SERVER_MESSAGE_H_