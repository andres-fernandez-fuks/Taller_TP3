//
// Created by andy on 3/11/20.
//

#include <iostream>
#include <string>
#include "Client.h"
#include "../common_src/ConnectionException.h"
#include "../common_src/Messenger.h"
#include "InputReader.h"

#define CHUNK_SIZE 64

Client::Client(const std::string& host, const std::string& port) :
                                                    socket(host, port){
}

void Client::forwardInput() {
    InputReader::readStdin(buffer);
    Messenger::sendMessage(socket, buffer);
    socket.shutDownConnection(SHUT_WR);
}

void Client::receiveResponse() {
    buffer = std::stringstream();
    Messenger::receiveMessage(socket, buffer);
}

void Client::printResponse() {
    printer.print(buffer.str());
}

int Client::handleRequest() {
    try {
        forwardInput();
        receiveResponse();
        printResponse();
    }
    catch(ConnectionException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
