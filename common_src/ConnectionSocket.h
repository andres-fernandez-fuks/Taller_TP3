//
// Created by andy on 21/11/20.
//

#include <sys/socket.h>

#ifndef TP3_FUNCIONANDO_CONNECTIONSOCKET_H
#define TP3_FUNCIONANDO_CONNECTIONSOCKET_H

typedef int (*connection_callback_t)(int sockfd, const struct sockaddr *addr,
                                     socklen_t addrlen);

#include "Socket.h"
#include "AcceptanceSocket.h"

class ConnectionSocket : public virtual Socket {
public:
    ConnectionSocket() = default;
    void listenToConnections() const;

protected:
    connection_callback_t connection_callback;
    int establishConnection(const char* port);
    int establishConnection(const char* host, const char* port);

private:
    int iterateAddressesForConnecting(struct addrinfo* results,
            bool should_bind);
    int establishConnection(const char* host, const char* port,
                                              bool should_bind, int ai_flags);
};


#endif //TP3_FUNCIONANDO_CONNECTIONSOCKET_H
