#ifndef SERVER_MESSAGE_H_
#define SERVER_MESSAGE_H_

#include <string>

class ServerMessage {
   private:
    std::string messageType;
    std::string message;

   public:
    ServerMessage(std::string message);
    std::string getMessage();
    ~ServerMessage();
};

#endif  // SERVER_MESSAGE_H_