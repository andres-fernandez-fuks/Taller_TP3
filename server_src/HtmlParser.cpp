//
// Created by andy on 5/11/20.
//

#include <iostream>
#include <sstream>
#include <string>
#include "HtmlParser.h"


HtmlRequest HtmlParser::parseInput(const std::string& input) {
    std::stringstream stream(input);
    HtmlRequest request;
    std::string line;
    bool parseBody = false;
    size_t line_counter = 1;
    while (std::getline(stream, line))
    {
        if (line_counter == 1)
            request.assemble(line);
        if (parseBody)
            request.addLineToBody(line);
        if (line.empty())
            parseBody = true;
        line_counter++;
    }
    return request;
}
