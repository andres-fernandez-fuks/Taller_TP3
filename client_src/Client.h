//
// Created by andy on 3/11/20.
//

#ifndef TP_3_CLIENT_H
#define TP_3_CLIENT_H

#include "../common_src/Socket.h"
#include "../server_src/HtmlParser.h"
#include "../common_src/Printer.h"
#include "../common_src/ClientSocket.h"
#include <sstream>
#include <string>

class Client {
public:
    Client(const std::string& host, const std::string& port);
    void forwardInput();
    void receiveResponse();
    void printResponse();
    int handleRequest();
    
private:
    ClientSocket socket;
    std::stringstream buffer;
    Printer printer;
};


#endif //TP_3_CLIENT_H
