//
// Created by andy on 21/11/20.
//

#include "DataSocket.h"
#include "ConnectionException.h"

int DataSocket::receiveMessage(unsigned char* buffer, size_t buffer_size) const{
    size_t bytes_read = 0;
    while (bytes_read < buffer_size) {
        int received = recv(socket_fd, &buffer[bytes_read],
                            buffer_size - bytes_read, 0);
        if (received < 0) {
            throw ConnectionException("Error en la recepción del mensaje");
        }
        if (received == 0)
            break;
        bytes_read += received;
    }
    return bytes_read;
}

int DataSocket::sendMessage(unsigned char* msg_chunk, size_t len) const {
    int bytes_written = 0;
    while (bytes_written < (int) len) {
        int sent = send(socket_fd, &msg_chunk[bytes_written],
                        len-bytes_written, MSG_NOSIGNAL);
        if (sent < 0)
            throw ConnectionException("Error en el envío del mensaje");
        bytes_written += sent;
    }
    return bytes_written;
}
