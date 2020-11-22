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



class Socket {
public:
    Socket() = default;
    ~Socket();
    bool isConnected() const;

    void closeConnection(bool should_shutdown);

    void shutDownConnection(int mode) const;

protected:
    int socket_fd = 0;
private:
    bool is_closed = false;
};



#endif //TP_3_SOCKET_H
