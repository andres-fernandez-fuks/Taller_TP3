//
// Created by andy on 21/11/20.
//

#include "AcceptanceSocket.h"

AcceptanceSocket::AcceptanceSocket(int file_descriptor) {
    socket_fd = file_descriptor;
}

AcceptanceSocket::AcceptanceSocket(AcceptanceSocket&& other) noexcept {
    this->socket_fd = other.socket_fd;
    other.socket_fd = -1;
}
AcceptanceSocket& AcceptanceSocket::operator=(AcceptanceSocket&& other)
        noexcept {
    this->socket_fd = other.socket_fd;
    other.socket_fd = -1;
    return *this;
}
