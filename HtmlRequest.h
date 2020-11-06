//
// Created by andy on 5/11/20.
//

#ifndef TP_3_HTMLREQUEST_H
#define TP_3_HTMLREQUEST_H


#include <string>

class HtmlRequest {

public:
    void assemble(std::string line);
    void setName(std::string name);
    void setResource(std::string resource);
    void setProtocol(std::string protocol);
    std::string getName();
    std::string getResource();
    std::string getBody();
    std::string getProtocol();
    void addLineToBody(std::string line);
    std::string getHeader();
    void print();

private:
    std::string name = "";
    std::string resource = "";
    std::string body = "";
    std::string protocol = "";
};


#endif //TP_3_HTMLREQUEST_H
