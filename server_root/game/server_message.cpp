#include "server_message.h"

ServerMessage::ServerMessage(std::string messageType, std::string message) : messageType(messageType), message(message) {
}

std::string ServerMessage::getMessageType() const {
    return messageType;
}

std::string ServerMessage::getMessage() const {
    return message;
}

ServerMessage::~ServerMessage() {
}