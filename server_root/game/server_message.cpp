#include "server_message.h"

ServerMessage::ServerMessage(std::string messageType, std::string message) : messageType(messageType), message(message) {
}

std::string ServerMessage::getMessage() {
    return message;
}

ServerMessage::~ServerMessage() {
}