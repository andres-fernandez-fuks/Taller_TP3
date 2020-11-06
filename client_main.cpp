#include <iostream>
#include "Client.h"

int main(int argc, char** argv) {
    Client client;
    std::string host = argv[1];
    std::string port = argv[2];
    client.establishConnection(host, port);
    client.forwardInput();
    client.receiveResponse();
    client.printResponse();
    return 0;
}
