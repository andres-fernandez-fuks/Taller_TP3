//
// Created by andy on 3/11/20.
//

#ifndef TP_3_SOCKET_H
#define TP_3_SOCKET_H

#include <sys/socket.h>
#include <string>
#include <netdb.h>
#include <sstream>
#include <mutex>

typedef int (*connection_callback_t)(int sockfd, const struct sockaddr *addr,
                                     socklen_t addrlen);

class Socket {
public:
    explicit Socket(bool is_server_type);
    explicit Socket(int connection_type);
    ~Socket();
    int establishConnection(const char* host, const char* port);
    Socket acceptConnection() const;
    int receiveMessage(unsigned char* buffer, size_t buffer_size) const;
    int sendMessage(unsigned char* msg_chunk, size_t len) const;
    void closeConnection(bool should_shutdown);
    void listenToConnections() const;
    void shutDownConnection(int mode) const;
    bool isConnected() const;
    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

private:
    int socket_fd;
    connection_callback_t connection_callback = nullptr;
    bool is_closed = false;
    int hints_ai_flags = 0;
    bool set_binding_options = false;

    struct addrinfo initializeHints() const;
    int iterateAddressesForConnecting(struct addrinfo* results);
};



#endif //TP_3_SOCKET_H
