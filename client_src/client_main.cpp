#include <string>
#include "Client.h"

int main(int argc, char** argv) {
    Client client;
    std::string host = argv[1];
    std::string port = argv[2];
    int request_ok = client.handleRequest(host, port);
    return request_ok;
}
