//
// Created by andy on 3/11/20.
//

#include <iostream>
#include <string>
#include "Client.h"
#include "../common_src/ConnectionException.h"

#define CHUNK_SIZE 64

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
    socket.shutDownConnection(SHUT_WR);
}

int Client::establishConnection(std::string host, std::string port) {
    return socket.establishConnection(host.c_str(), port.c_str());
}

void Client::receiveResponse() {
    buffer = std::stringbuf();
    socket.receiveMessage(buffer);
}

void Client::printResponse() {
    size_t len = buffer.str().length();
    size_t counter = 0;
    char aux_buffer[CHUNK_SIZE+1];
    while (counter < len) {
        int written = buffer.sgetn(aux_buffer, CHUNK_SIZE);
        aux_buffer[written] = '\0';
        std::cout << aux_buffer;
        counter += written;
    }
}
