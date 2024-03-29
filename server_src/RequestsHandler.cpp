//
// Created by andy on 7/11/20.
//

#include <string>
#include <utility>
#include "RequestsHandler.h"
#include "ClientHandler.h"
#include "../common_src/ConnectionException.h"

RequestsHandler::RequestsHandler(const std::string& port,
                                 const std::string& default_get_response) :
                                 keep_talking(true) {
    info_handler.setDefaultGetResponse(default_get_response);
    this-> port = port;
}

RequestsHandler::~RequestsHandler() = default;

void RequestsHandler::run() {
    socket.establishConnection(nullptr, port.c_str());
    socket.listenToConnections();
    while (keep_talking) {
        Socket acceptance_socket = socket.acceptConnection();
        if (!acceptance_socket.isConnected())
            break;

        auto* client_handler = new ClientHandler(std::move(acceptance_socket),
                                                 info_handler, printer);
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
}

void RequestsHandler::stopConnections() {
    keep_talking = false;
    socket.closeConnection(true);
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
