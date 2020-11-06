//
// Created by andy on 3/11/20.
//

#ifndef TP_3_CLIENT_H
#define TP_3_CLIENT_H

#include "Socket.h"
#include "HTMLParser.h"
#include <sstream>

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
