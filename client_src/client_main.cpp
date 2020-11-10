#include <iostream>
#include <string>
#include "Client.h"
#include "../common_src/ConnectionException.h"

int main(int argc, char** argv) {
    Client client;
    std::string host = argv[1];
    std::string port = argv[2];
    try {
        client.establishConnection(host, port);
        client.forwardInput();
        client.receiveResponse();
        client.printResponse();
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
