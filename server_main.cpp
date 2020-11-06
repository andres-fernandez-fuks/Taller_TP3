//
// Created by andy on 5/11/20.
//

#include <iostream>
#include "Server.h"
#include "InfoHandler.h"

int main(int argc, char** argv) {
    Server server;
    if (argc != 3)
        return 1;
    std::string port = argv[1];
    std::string info_file = argv[2];
    server.setDefaultGetResponse(info_file);
    server.establishConnection(port);
    server.receiveInput();
    server.respondToRequest();
    server.printResult();
    return 0;
}