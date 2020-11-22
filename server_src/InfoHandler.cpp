//
// Created by andy on 5/11/20.
//

#include <string>
#include <utility>
#include <sstream>
#include "InfoHandler.h"


std::string InfoHandler::handleRequest(const GetRequest& request) {
    std::string resource = request("resource");
    std::string prot = request("protocol");
    if (resource == "/")
        return prot + " 200 OK\nContent-Type: text/html\n\n" + default_response;
    if (info.contains(resource))
        return prot + " 200 OK\nContent-Type: text/html\n\n"+ info.at(resource);
    return prot + " 404 NOT FOUND\n\n";
}

std::string InfoHandler::handleRequest(const PostRequest &request) {
    std::string resource = request("resource");
    std::string protocol = request("protocol");
    if (resource == "/")
        return protocol + " 403 FORBIDDEN\n\n";

    std::string body = request("body");
    info.insert(resource, body);
    return protocol + " 200 OK\n\n" + body;
}

std::string InfoHandler::handleRequest(const InvalidRequest &request) {
    std::stringstream reply_stream;
    reply_stream << request("protocol");
    reply_stream << " 405 METHOD NOT ALLOWED\n\n";
    reply_stream << request("method");
    reply_stream << " es un comando desconocido\n";
    return reply_stream.str();
}


std::string InfoHandler::handleRequest(const HtmlRequest& request) {
    std::string method = request("method");
    if (method == "GET") {
        return handleRequest((GetRequest&) request);
    }
    if (method == "POST") {
        return handleRequest((PostRequest&) request);
    }
    return handleRequest((InvalidRequest&) request);
}

void InfoHandler::setDefaultGetResponse(const std::string& response) {
    default_response = response;
}
