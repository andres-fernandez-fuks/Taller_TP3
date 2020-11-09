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
    }
    catch(ConnectionException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    client.receiveResponse();
    client.printResponse();
    return 0;
}
