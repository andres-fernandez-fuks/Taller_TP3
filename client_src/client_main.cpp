#include <string>
#include "Client.h"

int main(int argc, char** argv) {
    std::string host = argv[1];
    std::string port = argv[2];
    Client client(host, port);
    int request_ok = client.handleRequest();
    return request_ok;
}
