//
// Created by andy on 5/11/20.
//

#ifndef TP_3_HTMLREQUEST_H
#define TP_3_HTMLREQUEST_H


#include <string>

class HtmlRequest {
public:
    void assemble(const std::string& line);
    std::string getName();
    std::string getResource();
    std::string getBody();
    std::string getProtocol();
    void addLineToBody(const std::string& line);
    std::string getHeader();

private:
    std::string name = "";
    std::string resource = "";
    std::string body = "";
    std::string protocol = "";
};


#endif //TP_3_HTMLREQUEST_H
