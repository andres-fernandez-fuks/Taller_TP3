//
// Created by andy on 8/11/20.
//

#include <cstring>
#include <string>
#include "ConnectionException.h"

ConnectionException::ConnectionException(const char* description) noexcept {
    size_t len = std::string(description).length();
    strncpy(msg_error, description, len);
}

ConnectionException::~ConnectionException() noexcept = default;

const char *ConnectionException::what() const noexcept {
    return msg_error;
}
