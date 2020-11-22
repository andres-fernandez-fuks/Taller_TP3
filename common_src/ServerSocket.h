//
// Created by andy on 21/11/20.
//

#ifndef TP3_FUNCIONANDO_SERVERSOCKET_H
#define TP3_FUNCIONANDO_SERVERSOCKET_H

#include <string>
#include "AcceptanceSocket.h"
#include "ConnectionSocket.h"

class ServerSocket : public ConnectionSocket {
public:
    explicit ServerSocket(const std::string& port);
    AcceptanceSocket acceptConnection() const;
};


#endif //TP3_FUNCIONANDO_SERVERSOCKET_H
