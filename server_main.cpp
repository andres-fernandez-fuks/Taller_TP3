//
// Created by andy on 5/11/20.
//

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "Server.h"
#include "InfoHandler.h"
#include "ClientHandler.h"
#include "AccepterThread.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }
    std::mutex m;
    std::string port = argv[1];
    std::string info_file = argv[2];
    AccepterThread accepter(port, info_file);
    accepter.start();

    m.lock();
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "q")
            break;
    }
    puts("TERMINANDO CONEXIONES");
    accepter.stopConnections();
    puts("CONEXIONES CERRADAS");
    m.unlock();
    accepter.join();
    puts("SALIENDO");
    return 0;
}