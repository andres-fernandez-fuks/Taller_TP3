//
// Created by andy on 3/11/20.
//

#include <iostream>
#include "Client.h"

void Client::readStdin() {
    std::string line;
    while (std::getline(std::cin, line)) {
        buffer.sputn(line.c_str(), line.length());
        buffer.sputc('\n');
    }
}

void Client::forwardInput() {
    readStdin();
    size_t message_size = buffer.str().length();
    socket.sendMessage(buffer, message_size);
}

int Client::establishConnection(std::string host, std::string port) {
    return socket.establishConnection(host.c_str(), port.c_str());
}

void Client::receiveResponse() {
    buffer = std::stringbuf();
    socket.receiveMessage(buffer);
}

void Client::printResponse() {
    int len = buffer.str().length();
    char aux[len+1];
    buffer.sgetn(aux, len);
    aux[len] = '\0';
    printf("%s\n", aux);
}