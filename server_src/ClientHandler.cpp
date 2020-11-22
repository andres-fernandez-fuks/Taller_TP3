//
// Created by andy on 7/11/20.
//

#include <string>
#include <iostream>
#include <utility>
#include "ClientHandler.h"
#include "../common_src/Messenger.h"

#define CHUNK_SIZE 64

ClientHandler::ClientHandler(AcceptanceSocket socket,
                             InfoHandler& info_handler_ref,
                             Printer& printer_ref) : socket(std::move(socket)),
     printer(printer_ref), finished(false), info_handler(info_handler_ref) {
}

ClientHandler::~ClientHandler() = default;

void ClientHandler::sendResponse(const std::string& response) {
    buffer = std::stringstream();
    buffer.write(response.c_str(), response.length());
    Messenger::sendMessage(socket, buffer);
}

HtmlRequest ClientHandler::parseInput() {
    std::string input = getStringFromBuffer();
    return HtmlParser::parseInput(input);
}

void ClientHandler::printResult() {
    printer.print(output);
}

void ClientHandler::closeConnection(bool should_shutdown) {
    socket.closeConnection(should_shutdown);
}

void ClientHandler::receiveInput() {
    Messenger::receiveMessage(socket, buffer);
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
    receiveInput();
    respondToRequest();
    printResult();
    finished = true;
}

bool ClientHandler::isDead() {
    return finished;
}

void ClientHandler::stop() {
    closeConnection(true);
}
