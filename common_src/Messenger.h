//
// Created by andy on 20/11/20.
//

#ifndef TP3_FUNCIONANDO_MESSENGER_H
#define TP3_FUNCIONANDO_MESSENGER_H


#include <sstream>
#include "Socket.h"
#include "DataSocket.h"

class Messenger {
public:
    static int sendMessage(const DataSocket& socket, std::stringstream& buffer);
    static int receiveMessage(const DataSocket& socket,
                              std::stringstream& buffer);
};


#endif //TP3_FUNCIONANDO_MESSENGER_H
