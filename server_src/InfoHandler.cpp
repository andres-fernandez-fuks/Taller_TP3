//
// Created by andy on 5/11/20.
//

#include <fstream>
#include <string>
#include <utility>
#include "InfoHandler.h"
#include "File.h"


std::string InfoHandler::handleRequest(GetRequest &request) {
    std::string resource = request.getResource();
    std::string prot = request.getProtocol();
    if (resource == "/")
        return prot + " 200 OK\nContent-Type: text/html\n\n" + default_response;
    if (info.find(resource) != info.end())
        return prot + " 200 OK\nContent-Type: text/html\n\n"+ info.at(resource);
    return prot + " 404 NOT FOUND\n\n";
}

std::string InfoHandler::handleRequest(PostRequest &request) {
    std::string resource = request.getResource();
    if (resource == "/")
        return request.getProtocol() + " 403 FORBIDDEN\n\n";

    std::string body = request.getBody();
    std::string protocol = request.getProtocol();
    info.insert(std::pair<std::string, std::string>(resource, body));
    return protocol + " 200 OK\n\n" + body;
}

std::string InfoHandler::handleRequest(InvalidRequest &request) {
    std::string reply;
    std::string method_name = request.getName();
    std::string protocol = request.getProtocol();
    reply += protocol + " 405 METHOD NOT ALLOWED\n\n";
    reply += method_name + " es un comando desconocido\n";
    return reply;
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

void InfoHandler::setDefaultGetResponse(const std::string& response) {
    default_response = response;
}
