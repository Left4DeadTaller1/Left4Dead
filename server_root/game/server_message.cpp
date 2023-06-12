#include "server_message.h"

ServerMessage::ServerMessage(std::string messageType, const std::vector<uint8_t>& message)
    : messageType(std::move(messageType)), message(message) {}

std::string ServerMessage::getMessageType() const {
    return messageType;
}

void ServerMessage::setMessageType(const std::string& messageType) {
    this->messageType = messageType;
}

std::vector<uint8_t> ServerMessage::getMessage() const {
    return message;
}

void ServerMessage::setMessage(const std::vector<uint8_t>& message) {
    this->message = message;
}