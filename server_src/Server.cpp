//
// Created by andy on 10/11/20.
//

#include <iostream>
#include <string>
#include "Server.h"
#include "RequestsHandler.h"
#include "InputChecker.h"
#include "../common_src/ConnectionException.h"
#include "FileReader.h"
#include "FileException.h"

int Server::handleRequests(const std::string& port,
                           const std::string& info_file) {
    std::string default_get_response;

    try {
        default_get_response = FileReader::getDefaultResponse(info_file);
    }
    catch(FileException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    RequestsHandler requests_handler(port, default_get_response);
    int result = 0;
    try {
        requests_handler.start();
        InputChecker::waitForInput();
    }
    catch(ConnectionException& e) {
        std::cout << e.what() << std::endl;
        result = 1;
    }
    requests_handler.stopConnections();
    requests_handler.join();
    return result;
}
