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
    int establishConnection(std::string port);
    int acceptConnection();
    void setDefaultGetResponse(std::string info_file);
    void closeConnection();

private:
    Socket connection_socket = Socket(1);

};


#endif //TP_3_SERVER_H
