//
// Created by andy on 9/11/20.
//

#ifndef TP_3_MEMORYEXCEPTION_H
#define TP_3_MEMORYEXCEPTION_H


#include <exception>
#define BUF_LEN 256

class MemoryException : std::exception {
public:
    explicit MemoryException(const char* description) noexcept;
    const char* what() const noexcept override;
    virtual ~MemoryException() noexcept;

private:
    char msg_error[BUF_LEN];
};

#endif //TP_3_MEMORYEXCEPTION_H
