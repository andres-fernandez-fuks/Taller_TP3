//
// Created by andy on 5/11/20.
//

#include <string>
#include "Server.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        puts("Cantidad incorrecta de argumentos");
        return 1;
    }

    std::string port = argv[1];
    std::string info_file = argv[2];
    int requests_ok = Server::handleRequests(port, info_file);
    return requests_ok;
}
