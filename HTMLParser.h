//
// Created by andy on 5/11/20.
//

#ifndef TP_3_HTMLPARSER_H
#define TP_3_HTMLPARSER_H


#include <string>
#include "GetRequest.h"
#include "PostRequest.h"
#include "HtmlRequest.h"

class HTMLParser {
public:
    HtmlRequest parseInput(std::string input);
    std::string serialize(HtmlRequest request);
    HtmlRequest deserialize(std::string serialized_request);
    void createResponse(GetRequest get_method);
    void createResponse(PostRequest post_method);
    void createResponse(std::string other_method);
};


#endif //TP_3_HTMLPARSER_H
