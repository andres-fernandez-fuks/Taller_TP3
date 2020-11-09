//
// Created by andy on 8/11/20.
//

#ifndef TP_3_FILEEXCEPTION_H
#define TP_3_FILEEXCEPTION_H


#include <exception>
#include <string>

#define BUF_LEN 256

class FileException : std::exception {
public:
    explicit FileException(const char* description) noexcept;
    const char* what() const noexcept override;
    virtual ~FileException() noexcept;
private:
    char msg_error[BUF_LEN];
};


#endif //TP_3_FILEEXCEPTION_H
