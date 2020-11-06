//
// Created by andy on 3/11/20.
//

#ifndef TP_3_SERVER_H
#define TP_3_SERVER_H


#include <sstream>
#include "Socket.h"
#include "HTMLParser.h"
#include "InfoHandler.h"

class Server {
public:
    int receiveInput();
    int establishConnection(std::string port);
    void getBuffer();
    void printMessage(int len);
    void setDefaultGetResponse(std::string info_file);
    void respondToRequest();
    void sendResponse(std::string response);
    void printResult();

private:
    Socket connection_socket = Socket(1);
    Socket acceptance_socket = Socket(1);
    std::stringbuf buffer;
    HTMLParser parser;
    InfoHandler info_handler;
    std::string output;

    std::string getStringFromBuffer();
    HtmlRequest parseInput();
};


#endif //TP_3_SERVER_H
