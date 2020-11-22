//
// Created by andy on 3/11/20.
//

#ifndef TP_3_CLIENT_H
#define TP_3_CLIENT_H

#include "../common_src/Socket.h"
#include "../server_src/HtmlParser.h"
#include "../common_src/Printer.h"
#include <sstream>
#include <string>

class Client {
public:
    void forwardInput();
    int establishConnection(const std::string& host, const std::string& port);
    void receiveResponse();
    void printResponse();
    int handleRequest(const std::string& host, const std::string& port);
    
private:
    Socket socket = Socket(false);
    std::stringstream buffer;
    Printer printer;
};


#endif //TP_3_CLIENT_H
