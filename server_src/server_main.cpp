//
// Created by andy on 5/11/20.
//

#include <iostream>
#include <string>
#include <mutex>
#include "Server.h"
#include "InputChecker.h"
#include "FileReader.h"
#include "FileException.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }
    std::mutex m;
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
    Server server(port, default_get_response);
    server.start();
    m.lock();
    InputChecker checker;
    checker.waitForInput();
    server.stopConnections();
    m.unlock();
    server.join();
    return 0;
}
