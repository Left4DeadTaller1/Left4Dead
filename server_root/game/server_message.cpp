#include "server_message.h"

ServerMessage::ServerMessage(std::string message) : message(message) {
}

std::string ServerMessage::getMessage() {
    return message;
}

ServerMessage::~ServerMessage() {
}