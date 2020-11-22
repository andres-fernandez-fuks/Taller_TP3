//
// Created by andy on 21/11/20.
//

#include <string>
#include "ClientSocket.h"

ClientSocket::ClientSocket(const std::string& host, const std::string& port) {
    connection_callback = &connect;
    establishConnection(host.c_str(), port.c_str());
}
