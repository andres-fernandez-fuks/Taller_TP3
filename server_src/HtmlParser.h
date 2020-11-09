//
// Created by andy on 5/11/20.
//

#ifndef TP_3_HTMLPARSER_H
#define TP_3_HTMLPARSER_H


#include <string>
#include "GetRequest.h"
#include "PostRequest.h"
#include "HtmlRequest.h"

class HtmlParser {
public:
    HtmlRequest parseInput(std::string input);
};


#endif //TP_3_HTMLPARSER_H
