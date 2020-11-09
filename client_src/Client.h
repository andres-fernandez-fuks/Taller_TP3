//
// Created by andy on 3/11/20.
//

#ifndef TP_3_CLIENT_H
#define TP_3_CLIENT_H

#include "../common_src/Socket.h"
#include "../server_src/HtmlParser.h"
#include <sstream>
#include <string>

class Client {
public:
    void forwardInput();
    int establishConnection(std::string host, std::string port);
    void receiveResponse();
    void printResponse();
    
private:
    Socket socket = Socket(0);
    std::stringbuf buffer;
    void readStdin();
};


#endif //TP_3_CLIENT_H
