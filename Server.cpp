//
// Created by andy on 3/11/20.
//

#include <iostream>
#include "Server.h"

int Server::receiveInput() {
    return acceptance_socket.receiveMessage(buffer);
}

int Server::establishConnection(std::string port) {
    connection_socket.establishConnection(NULL, port.c_str());
    connection_socket.acceptConnection(acceptance_socket);
    return 0;
}

void Server::respondToRequest() {
    HtmlRequest request = parseInput();
    output = request.getHeader();
    std::string reply = info_handler.handleRequest(request);
    sendResponse(reply);
}

void Server::setDefaultGetResponse(std::string info_file) {
    info_handler.setDefaultGetResponse(info_file);
}

std::string Server::getStringFromBuffer() {
    return buffer.str();
}

void Server::sendResponse(std::string response) {
    buffer = std::stringbuf();
    buffer.sputn(response.c_str(), response.length());
    acceptance_socket.sendMessage(buffer, buffer.str().length());
}

HtmlRequest Server::parseInput() {
    std::string input = getStringFromBuffer();
    return parser.parseInput(input);
}

void Server::printResult() {
    std::cout << output << std::endl;
}