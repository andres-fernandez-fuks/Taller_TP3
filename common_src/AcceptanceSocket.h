//
// Created by andy on 21/11/20.
//

#ifndef TP3_FUNCIONANDO_ACCEPTANCESOCKET_H
#define TP3_FUNCIONANDO_ACCEPTANCESOCKET_H


#include "DataSocket.h"

class AcceptanceSocket : public DataSocket {
public:
    explicit AcceptanceSocket(int file_descriptor);
    AcceptanceSocket(const AcceptanceSocket& other) = delete;
    AcceptanceSocket& operator=(const AcceptanceSocket& other) = delete;
    AcceptanceSocket(AcceptanceSocket&& AcceptanceSocket) noexcept;
    AcceptanceSocket& operator=(AcceptanceSocket&& other) noexcept;
};


#endif //TP3_FUNCIONANDO_ACCEPTANCESOCKET_H
