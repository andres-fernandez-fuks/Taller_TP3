//
// Created by andy on 21/11/20.
//

#ifndef TP3_FUNCIONANDO_CLIENTSOCKET_H
#define TP3_FUNCIONANDO_CLIENTSOCKET_H

#include <string>
#include "ConnectionSocket.h"
#include "DataSocket.h"

class ClientSocket : public ConnectionSocket, public DataSocket {
public:
    ClientSocket(const std::string& host, const std::string& port);
};


#endif //TP3_FUNCIONANDO_CLIENTSOCKET_H
