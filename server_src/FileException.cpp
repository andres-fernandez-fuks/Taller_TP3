//
// Created by andy on 8/11/20.
//

#include <cstring>
#include <string>
#include "FileException.h"

FileException::FileException(const char* description) noexcept {
    size_t len = std::string(description).length();
    strncpy(msg_error, description, len);
}

FileException::~FileException() noexcept = default;

const char *FileException::what() const noexcept {
    return msg_error;
}
