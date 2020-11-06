//
// Created by andy on 5/11/20.
//

#include <iostream>
#include <sstream>
#include "HTMLParser.h"


HtmlRequest HTMLParser::parseInput(std::string input) {
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
        if (line == "")
            parseBody = true;
        line_counter++;
    }
    return request;
}

HtmlRequest HTMLParser::deserialize(std::string serialized_request) {
    HtmlRequest request;
    std::istringstream string_stream(serialized_request);
    std::string name;
    std::getline(string_stream, name);
    request.setName(name);
    std::string resource;
    std::getline(string_stream, resource);
    request.setResource(resource);
    std::string protocol;
    std::getline(string_stream, protocol);
    request.setProtocol(protocol);
    std::string body_line;
    while (std::getline(string_stream, body_line))
        request.addLineToBody(body_line);
    return request;
}

std::string HTMLParser::serialize(HtmlRequest request) {
    std::string response;
    response += request.getName();
    response += '\n';
    response += request.getResource();
    response += '\n';
    response += request.getProtocol();
    response += '\n';
    if (request.getName() == "POST")
        response += request.getBody();

    return response;
}
