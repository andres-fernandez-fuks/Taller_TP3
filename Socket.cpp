//
// Created by andy on 3/11/20.
//

#include <unistd.h>
#include <cstring>
#include "Socket.h"
#define CONNECT_TYPE 0
#define BIND_TYPE 1

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
        //freeaddrinfo(results);
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

void Socket::iterateAddressesForConnecting() {
    struct addrinfo* address;
    setBindingOptions(connection_type, socket_fd);
    for (address = results; address != NULL; address = address->ai_next) {
        socket_fd = socket(address->ai_family, address->ai_socktype,
                                 address->ai_protocol);
        if (socket_fd == -1)
            continue;
        if (connection_callback(socket_fd, address->ai_addr,
                                      address->ai_addrlen) != -1) {
            connection_info = address;
            break;
        }
    }
}

int Socket::establishConnection(const char* host, const char* port) {
    int search;
    initializeHints();
    search = getaddrinfo(NULL, port, &hints, &results);
    if (search != 0)
        printf("%s\n", gai_strerror(search));
    iterateAddressesForConnecting();
    if (!connection_info)
        return 1;
    return 0;
}

void Socket::setConnection(int fd) {
    socket_fd = fd;
}

int Socket::acceptConnection() {

    int acceptance_fd = accept(socket_fd,
                              (struct sockaddr*) &connection_info-> ai_addr,
                               (socklen_t*) &connection_info->ai_addrlen);
    return acceptance_fd;
}

int Socket::receiveMessage(std::stringbuf& buffer) {
    size_t counter = 0;
    char* aux_buf = (char*) malloc(64);
    while (true) {
        int bytes_recv = recv(socket_fd, aux_buf, 64, 0);
        if (bytes_recv < 0) {
            puts("ROMPE ACA");
            throw -1;
        }
        if (bytes_recv == 0)
            break;
        counter += bytes_recv;
        buffer.sputn(aux_buf, bytes_recv);
    }
    free(aux_buf);
    buffer.sputc('\0');
    return counter;
}

size_t min(size_t size_1, size_t size_2) {
    if (size_1 < size_2)
        return size_1;
    return size_2;
}

int Socket::sendMessage(std::stringbuf& buffer, size_t len) {
    size_t counter = 0;
    size_t bytes_left = len;
    char* array = (char*) malloc(len);
    buffer.sgetn(array, len);
    while (counter < len) {
        size_t send_size = min(64, bytes_left);
        int bytes_written = send(socket_fd, &array[counter], send_size,
                                 MSG_NOSIGNAL);
        if (bytes_written < 0)
            return 1;
        counter += bytes_written;
        bytes_left -= bytes_written;
    }
    free(array);
    return 0;
}

void Socket::closeConnection(bool should_shutdown) {
    if (is_closed)
        return;
    if (should_shutdown)
        shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    is_closed = true;
}

void Socket::listenToConnections() {
    listen(socket_fd, 15);
}

void Socket::shutDownConnection(int mode) {
    shutdown(socket_fd, mode);
}
