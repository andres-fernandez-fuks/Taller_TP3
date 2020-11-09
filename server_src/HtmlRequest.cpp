//
// Created by andy on 5/11/20.
//

#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "HtmlRequest.h"

template <class Container>
void split(const std::string& str, Container& cont) {
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(cont));
}

void HtmlRequest::assemble(const std::string& line) {
    std::vector<std::string> vector;
    split(line, vector);
    name = vector[0];
    resource = vector[1];
    protocol = vector[2];
}

void HtmlRequest::addLineToBody(const std::string& line) {
    body += line + '\n';
}

std::string HtmlRequest::getName() {
    return name;
}

std::string HtmlRequest::getResource() {
    return resource;
}

std::string HtmlRequest::getBody() {
    return body;
}

std::string HtmlRequest::getProtocol() {
    return protocol;
}

std::string HtmlRequest::getHeader() {
    return name + ' ' + resource + ' ' + protocol + '\n';
}
