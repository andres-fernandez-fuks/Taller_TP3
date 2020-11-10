//
// Created by andy on 5/11/20.
//

#include <iostream>
#include <string>
#include "RequestsHandler.h"
#include "InputChecker.h"
#include "FileReader.h"
#include "FileException.h"
#include "../common_src/ConnectionException.h"
#include "Server.h"

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

    int requests_ok = Server::handleRequests(port, default_get_response);
    return requests_ok;
}
