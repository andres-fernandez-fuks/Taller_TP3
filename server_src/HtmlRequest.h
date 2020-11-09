//
// Created by andy on 5/11/20.
//

#ifndef TP_3_HTMLREQUEST_H
#define TP_3_HTMLREQUEST_H


#include <string>

class HtmlRequest {
public:
    void assemble(const std::string& line);
    void addLineToBody(const std::string& line);
    std::string operator()(const std::string& attribute_name) const;

private:
    std::string method;
    std::string resource;
    std::string body;
    std::string protocol;
};


#endif //TP_3_HTMLREQUEST_H
