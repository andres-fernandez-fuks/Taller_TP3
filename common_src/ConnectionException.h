 //
// Created by andy on 8/11/20.
//

#ifndef TP_3_CONNECTIONEXCEPTION_H
#define TP_3_CONNECTIONEXCEPTION_H

#include <exception>
#include <string>
#include "AcceptanceSocket.h"

#define BUF_LEN 256

class ConnectionException : std::exception {
public:
    explicit ConnectionException(const char* description) noexcept;
    const char* what() const noexcept override;
    ~ConnectionException() noexcept override;
    
private:
    char msg_error[BUF_LEN] = "";
};

#endif //TP_3_CONNECTIONEXCEPTION_H
