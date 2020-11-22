//
// Created by andy on 21/11/20.
//

#include <string>
#include "ServerSocket.h"

ServerSocket::ServerSocket(const std::string& port){
    connection_callback = &bind;
    establishConnection(port.c_str());
}

AcceptanceSocket ServerSocket::acceptConnection() const {
    int acceptance_fd = accept(socket_fd, nullptr, nullptr);
    return AcceptanceSocket(acceptance_fd);
}
