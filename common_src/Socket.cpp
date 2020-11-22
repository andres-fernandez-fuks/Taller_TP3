//
// Created by andy on 3/11/20.
//

#include <unistd.h>
#include <cstring>
#include "Socket.h"
#include "ConnectionException.h"

#define CHUNK_SIZE 64

Socket::Socket(bool is_server_type) {
    socket_fd = 0;
    this-> connection_callback = is_server_type ? &bind : &connect;
    this-> hints_ai_flags = is_server_type ? 1 : 0;
    this -> set_binding_options = is_server_type;
}

Socket::Socket(int file_descriptor) {
    this-> socket_fd = file_descriptor;
}

Socket::~Socket() {
    shutdown(socket_fd,SHUT_RDWR);
    close(socket_fd);
}

struct addrinfo Socket::initializeHints() const {
    struct addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = hints_ai_flags;
    return hints;
}

void setBindingOptions(int socket_fd) {
    int val = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

int Socket::iterateAddressesForConnecting(struct addrinfo* results) {
    struct addrinfo* address;
    if (set_binding_options)
        setBindingOptions(socket_fd);
    for (address = results; address != nullptr; address = address->ai_next) {
        socket_fd = socket(address->ai_family, address->ai_socktype,
                                 address->ai_protocol);
        if (socket_fd == -1)
            continue;
        if (connection_callback(socket_fd, address->ai_addr,
                                      address->ai_addrlen) != -1) {
            freeaddrinfo(results);
            return 0;
        }
    }
    return 1;
}

int Socket::establishConnection(const char* host, const char* port) {
    int search;
    struct addrinfo hints = initializeHints();
    struct addrinfo* results;
    search = getaddrinfo(host, port, &hints, &results);
    if (search != 0)
        printf("%s\n", gai_strerror(search));
    int val_connection = iterateAddressesForConnecting(results);
    if (val_connection != 0)
        throw ConnectionException("Error al intentar establecer la conexión");
    return 0;
}

Socket Socket::acceptConnection() const {
    int acceptance_fd = accept(socket_fd, nullptr, nullptr);
    return Socket(acceptance_fd);
}

int Socket::receiveMessage(unsigned char* buffer, size_t buffer_size) const {
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

int Socket::sendMessage(unsigned char* msg_chunk, size_t len) const {
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

bool Socket::isConnected() const {
    return socket_fd > 0;
}

Socket::Socket(Socket&& other) noexcept {
    this->socket_fd = other.socket_fd;
    other.socket_fd = -1;
}
Socket& Socket::operator=(Socket&& other) noexcept {
    this->socket_fd = other.socket_fd;
    other.socket_fd = -1;
    return *this;
}
