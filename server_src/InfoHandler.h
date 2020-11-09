//
// Created by andy on 5/11/20.
//

#ifndef TP_3_INFOHANDLER_H
#define TP_3_INFOHANDLER_H


#include <string>
#include <map>
#include "HtmlRequest.h"
#include "GetRequest.h"
#include "PostRequest.h"
#include "InvalidRequest.h"

class InfoHandler {
public:
    std::string handleRequest(const HtmlRequest& request);
    std::string handleRequest(const GetRequest& request);
    std::string handleRequest(const PostRequest& request);
    static std::string handleRequest(const InvalidRequest& request);
    void setDefaultGetResponse(const std::string& file_path);
private:
    std::map<std::string,std::string> info;
    std::string default_response;
};


#endif //TP_3_INFOHANDLER_H
