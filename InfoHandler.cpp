//
// Created by andy on 5/11/20.
//

#include <fstream>
#include "InfoHandler.h"

std::string InfoHandler::handleRequest(GetRequest &request) {
    std::string resource = request.getResource();
    if (resource == "/")
        return "HTTP 200 OK\nContent-Type: text/html\n\n" + default_response;
    if (info.find(resource) != info.end())
        return "HTTP 200 OK\nContent-Type: text/html\n\n" + info.at(resource);
    return "HTTP 404 NOT FOUND\n\n";
}

std::string InfoHandler::handleRequest(PostRequest &request) {
    std::string resource = request.getResource();
    if (resource.empty())
        return "HTTP 403 FORBIDDEN";

    std::string body = request.getBody();
    info.insert(std::pair<std::string, std::string>(resource, body));
    return body;
}

std::string InfoHandler::handleRequest(InvalidRequest &request) {
    return "HTTP 405 METHOD NOT ALLOWED\n\n";
}


std::string InfoHandler::handleRequest(HtmlRequest& request) {
    std::string request_name = request.getName();
    if (request_name == "GET") {
        return handleRequest((GetRequest&) request);
    }
    if (request_name == "POST") {
        return handleRequest((PostRequest&) request);
    }
    return handleRequest((InvalidRequest&) request);
}

void InfoHandler::setDefaultGetResponse(std::string file_path) {
    std::ifstream infile(file_path);
    std::string line;
    while (getline(infile, line)) {
        default_response += line +'\n';
    }
}