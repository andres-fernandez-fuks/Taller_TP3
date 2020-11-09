//
// Created by andy on 9/11/20.
//

#include <string>
#include <cstring>
#include "MemoryException.h"

MemoryException::MemoryException(const char* description) noexcept {
    size_t len = std::string(description).length();
    strncpy(msg_error, description, len);
}

MemoryException::~MemoryException() noexcept = default;

const char *MemoryException::what() const noexcept {
    return msg_error;
}
