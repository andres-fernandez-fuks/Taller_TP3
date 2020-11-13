//
// Created by andy on 3/11/20.
//

#include <unistd.h>
#include <cstring>
#include "Socket.h"
#include "ConnectionException.h"

#define CONNECT_TYPE 0
#define BIND_TYPE 1
#define CHUNK_SIZE 64

void Socket::setConnectionCallback() {
    switch (connection_type) {
        case CONNECT_TYPE:
            connection_callback = &connect;
            break;
        case BIND_TYPE:
            connection_callback = &bind;
            break;
    }
}

Socket::Socket(int connection_type) {
    socket_fd = 0;
    this->connection_type = connection_type;
    setConnectionCallback();
}

Socket::~Socket() {
    shutdown(socket_fd,SHUT_RDWR);
    if (results)
        freeaddrinfo(results);
    close(socket_fd);
}

void Socket::initializeHints() {
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (connection_type == CONNECT_TYPE)
        hints.ai_flags = 0;
    else
        hints.ai_flags = AI_PASSIVE;
}

void setBindingOptions(int connection_type, int socket_fd) {
    if (connection_type == CONNECT_TYPE)
        return;
    int val = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

int Socket::iterateAddressesForConnecting() {
    struct addrinfo* address;
    setBindingOptions(connection_type, socket_fd);
    for (address = results; address != nullptr; address = address->ai_next) {
        socket_fd = socket(address->ai_family, address->ai_socktype,
                                 address->ai_protocol);
        if (socket_fd == -1)
            continue;
        if (connection_callback(socket_fd, address->ai_addr,
                                      address->ai_addrlen) != -1) {
            connection_info = address;
            return 0;
        }
    }
    return 1;
}

int Socket::establishConnection(const char* host, const char* port) {
    int search;
    initializeHints();
    search = getaddrinfo(host, port, &hints, &results);
    if (search != 0)
        printf("%s\n", gai_strerror(search));
    int val_connection = iterateAddressesForConnecting();
    if (val_connection != 0)
        throw ConnectionException("Error al intentar establecer la conexión");
    return 0;
}

void Socket::setConnection(int fd) {
    socket_fd = fd;
}

int Socket::acceptConnection() const {
    int acceptance_fd = accept(socket_fd, nullptr, nullptr);
    return acceptance_fd;
}

int Socket::receiveMessage(std::stringbuf& buffer) const {
    size_t counter = 0;
    char aux_buf[CHUNK_SIZE];
    while (true) {
        int bytes_recv = recv(socket_fd, aux_buf, CHUNK_SIZE, 0);
        if (bytes_recv < 0) {
            throw ConnectionException("Error en la recepción del mensaje");
        }
        if (bytes_recv == 0)
            break;
        counter += bytes_recv;
        buffer.sputn(aux_buf, bytes_recv);
        memset(aux_buf, 0, CHUNK_SIZE);
    }
    buffer.sputc('\0');
    return counter;
}

size_t minimum(size_t size_1, size_t size_2) {
   return (size_1 < size_2) ? size_1 : size_2;
}

int Socket::sendMessage(std::stringbuf& buffer, size_t len) const {
    size_t counter = 0;
    size_t bytes_left = len;
    char array[CHUNK_SIZE];
    while (counter < len) {
        size_t send_size = minimum(CHUNK_SIZE, bytes_left);
        buffer.sgetn(array, send_size);
        int bytes_written = 0;
        while (bytes_written < (int) send_size) {
            int sent = send(socket_fd, &array[bytes_written],
                            send_size-bytes_written, MSG_NOSIGNAL);
            if (sent < 0)
                throw ConnectionException("Error en el envío del mensaje");
            bytes_written += sent;
        }
        memset(array, 0, CHUNK_SIZE);
        counter += send_size;
        bytes_left -= bytes_written;
    }
    return counter;
}

void Socket::closeConnection(bool should_shutdown) {
    if (is_closed)
        return;
    if (should_shutdown)
        shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    is_closed = true;
}

void Socket::listenToConnections() const {
    listen(socket_fd, 15);
}

void Socket::shutDownConnection(int mode) const {
    shutdown(socket_fd, mode);
}
