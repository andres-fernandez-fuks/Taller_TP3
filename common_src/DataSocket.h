//
// Created by andy on 21/11/20.
//

#ifndef TP3_FUNCIONANDO_DATASOCKET_H
#define TP3_FUNCIONANDO_DATASOCKET_H


#include "Socket.h"

class DataSocket : public virtual Socket {
public:
    int receiveMessage(unsigned char* buffer, size_t buffer_size) const;
    int sendMessage(unsigned char* msg_chunk, size_t len) const;
};


#endif //TP3_FUNCIONANDO_DATASOCKET_H
