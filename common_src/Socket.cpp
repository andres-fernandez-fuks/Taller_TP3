//
// Created by andy on 3/11/20.
//

#include <unistd.h>
#include <cstring>
#include "Socket.h"
#include "ConnectionException.h"

#define CHUNK_SIZE 64

Socket::~Socket() {
    shutdown(socket_fd,SHUT_RDWR);
    close(socket_fd);
}

void Socket::closeConnection(bool should_shutdown) {
    if (is_closed)
        return;
    if (should_shutdown)
        shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    is_closed = true;
}

bool Socket::isConnected() const {
    return socket_fd > 0;
}

void Socket::shutDownConnection(int mode) const {
    shutdown(socket_fd, mode);
}

