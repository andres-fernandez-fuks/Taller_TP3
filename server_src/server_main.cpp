//
// Created by andy on 5/11/20.
//

#include <iostream>
#include <string>
#include "Server.h"
#include "InputChecker.h"
#include "FileReader.h"
#include "FileException.h"
#include "../common_src/ConnectionException.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        puts("Cantidad incorrecta de argumentos");
        return 1;
    }

    std::string port = argv[1];
    std::string info_file = argv[2];
    std::string default_get_response;
    try {
        default_get_response = FileReader::getDefaultResponse(info_file);
    }
    catch(FileException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    Server server;
    try {
        server.setConnection(port, default_get_response);
        server.start();
        InputChecker::waitForInput();
        server.stopConnections();
        server.join();
    }
    catch(ConnectionException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
