//
// Created by andy on 7/11/20.
//

#include <mutex>
#include <string>
#include "RequestsHandler.h"
#include "ClientHandler.h"
#include "../common_src/ConnectionException.h"

RequestsHandler::RequestsHandler(const std::string& port,
                                 const std::string& default_get_response) :
                                 keep_talking(true) {
    this-> default_response = default_get_response;
    this-> port = port;
}

RequestsHandler::~RequestsHandler() {}

void RequestsHandler::run() {
    std::mutex m;
    m.lock();
    socket.establishConnection(nullptr, port.c_str());
    socket.listenToConnections();
    while (keep_talking) {
        int client_fd = socket.acceptConnection();
        if (client_fd < 0)
            break;

        auto* client_handler = new ClientHandler(client_fd);
        client_handler-> setDefaultResponse(default_response);
        clients.push_back(client_handler);
        try {
            client_handler-> start();
        }
        catch(ConnectionException& e) {
            break;
        }
        cleanConnections();
    }
    closeAllConnections();
    m.unlock();
}

void RequestsHandler::stopConnections() {
    std::mutex m;
    m.lock();
    keep_talking = false;
    socket.closeConnection(true);
    m.unlock();
}

void RequestsHandler::cleanConnections() {
    std::atomic<int> counter(0);
    for (auto each_client : clients) {
        if (each_client->isDead()){
            each_client->join();
            delete(each_client);
            clients.erase(clients.begin()+counter);
        }
        counter++;
    }
}

void RequestsHandler::closeAllConnections() {
    for (auto each_client : clients) {
        if (!each_client)
            continue;
        each_client->stop();
        each_client->join();
        delete(each_client);
    }
    if (keep_talking)
        throw ConnectionException("Error al intentar establecer la conexion");
}
