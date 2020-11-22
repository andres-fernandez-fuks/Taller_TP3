//
// Created by andy on 21/11/20.
//

#include "ConnectionSocket.h"
#include "ConnectionException.h"


struct addrinfo initializeHints(int ai_flags) {
    struct addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = ai_flags;
    return hints;
}

void setBindingOptions(int socket_fd) {
    int val = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

int ConnectionSocket::iterateAddressesForConnecting(struct addrinfo* results,
                                                    bool should_bind) {
    struct addrinfo* address;
    if (should_bind)
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

int ConnectionSocket::establishConnection(const char* host, const char* port,
                                          bool should_bind, int ai_flags) {
    int search;
    struct addrinfo hints = initializeHints(ai_flags);
    struct addrinfo* results;
    search = getaddrinfo(host, port, &hints, &results);
    if (search != 0)
        printf("%s\n", gai_strerror(search));
    int val_connection = iterateAddressesForConnecting(results, should_bind);
    if (val_connection != 0)
        throw ConnectionException("Error al intentar establecer la conexión");
    return 0;
}

int ConnectionSocket::establishConnection(const char* port) {
    return establishConnection(nullptr, port, true, AI_PASSIVE);
}

int ConnectionSocket::establishConnection(const char* host, const char* port) {
    return establishConnection(host, port, false, 0);
}

void ConnectionSocket::listenToConnections() const {
    listen(socket_fd, 15);
}

