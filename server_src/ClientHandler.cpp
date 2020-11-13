//
// Created by andy on 7/11/20.
//

#include <string>
#include <iostream>
#include <mutex>
#include "ClientHandler.h"

ClientHandler::ClientHandler(int socket_fd, std::mutex& mutex) : m(mutex),
                                    finished(false){
    socket.setConnection(socket_fd);
}

ClientHandler::~ClientHandler() = default;

void ClientHandler::sendResponse(const std::string& response) {
    buffer = std::stringbuf();
    buffer.sputn(response.c_str(), response.length());
    socket.sendMessage(buffer, buffer.str().length());
}

HtmlRequest ClientHandler::parseInput() {
    std::string input = getStringFromBuffer();
    return parser.parseInput(input);
}

void ClientHandler::printResult() {
    std::cout << output;
}

void ClientHandler::closeConnection(bool should_shutdown) {
    socket.closeConnection(should_shutdown);
}

void ClientHandler::receiveInput() {
    buffer = std::stringbuf();
    socket.receiveMessage(buffer);
}

std::string ClientHandler::getStringFromBuffer() {
    return buffer.str();
}

void ClientHandler::respondToRequest() {
    HtmlRequest request = parseInput();
    output = request("header");
    std::string response = info_handler.handleRequest(request);
    sendResponse(response);
    closeConnection(true);
}

void  ClientHandler::run() {
    m.lock();
    receiveInput();
    respondToRequest();
    printResult();
    finished = true;
    m.unlock();
}

void ClientHandler::setDefaultResponse(const std::string& default_response) {
    info_handler.setDefaultGetResponse(default_response);
}

bool ClientHandler::isDead() {
    return finished;
}

void ClientHandler::stop() {
    closeConnection(true);
}
