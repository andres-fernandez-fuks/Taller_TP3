//
// Created by andy on 5/11/20.
//

#ifndef TP_3_INFOHANDLER_H
#define TP_3_INFOHANDLER_H


#include <string>
#include <map>
#include <mutex>
#include "HtmlRequest.h"
#include "GetRequest.h"
#include "PostRequest.h"
#include "InvalidRequest.h"
#include "ProtectedMap.h"

class InfoHandler {
public:
    std::string handleRequest(const HtmlRequest& request);
    std::string handleRequest(const GetRequest& request);
    std::string handleRequest(const PostRequest& request);
    static std::string handleRequest(const InvalidRequest& request);
    void setDefaultGetResponse(const std::string& file_path);
private:
    ProtectedMap info;
    std::string default_response;
};


#endif //TP_3_INFOHANDLER_H
