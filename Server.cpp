//
// Created by andy on 3/11/20.
//

#include <iostream>
#include "Server.h"

int Server::establishConnection(std::string port) {
    connection_socket.establishConnection(NULL, port.c_str());
    connection_socket.listenToConnections();
    return 0;
}

int Server::acceptConnection() {
    return connection_socket.acceptConnection();
}