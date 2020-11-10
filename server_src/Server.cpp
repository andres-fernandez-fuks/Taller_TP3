//
// Created by andy on 10/11/20.
//

#include <iostream>
#include <string>
#include "Server.h"
#include "RequestsHandler.h"
#include "InputChecker.h"
#include "../common_src/ConnectionException.h"

int Server::handleRequests(const std::string& port,
                           const std::string& default_get_response) {
    RequestsHandler request_handler;
    try {
        request_handler.setConnection(port, default_get_response);
        request_handler.start();
        InputChecker::waitForInput();
        request_handler.stopConnections();
        request_handler.join();
    }
    catch(ConnectionException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
